#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hostapd_rate_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  rate; } ;
struct hostapd_iface {size_t num_rates; TYPE_1__* conf; struct hostapd_rate_data* current_rates; struct hostapd_rate_data* basic_rates; } ;
struct hostapd_hw_modes {int mode; int num_rates; int /*<<< orphan*/ * rates; } ;
struct TYPE_2__ {int* basic_rates; int* supported_rates; int /*<<< orphan*/  require_ht; int /*<<< orphan*/  ieee80211n; } ;

/* Variables and functions */
#define  HOSTAPD_MODE_IEEE80211A 131 
#define  HOSTAPD_MODE_IEEE80211AD 130 
#define  HOSTAPD_MODE_IEEE80211B 129 
#define  HOSTAPD_MODE_IEEE80211G 128 
 int /*<<< orphan*/  HOSTAPD_RATE_BASIC ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ hostapd_rate_found (int*,int /*<<< orphan*/ ) ; 
 struct hostapd_rate_data* os_calloc (int,int) ; 
 int /*<<< orphan*/  os_free (struct hostapd_rate_data*) ; 
 struct hostapd_rate_data* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (struct hostapd_rate_data*,int*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int hostapd_prepare_rates(struct hostapd_iface *iface,
			  struct hostapd_hw_modes *mode)
{
	int i, num_basic_rates = 0;
	int basic_rates_a[] = { 60, 120, 240, -1 };
	int basic_rates_b[] = { 10, 20, -1 };
	int basic_rates_g[] = { 10, 20, 55, 110, -1 };
	int *basic_rates;

	if (iface->conf->basic_rates)
		basic_rates = iface->conf->basic_rates;
	else switch (mode->mode) {
	case HOSTAPD_MODE_IEEE80211A:
		basic_rates = basic_rates_a;
		break;
	case HOSTAPD_MODE_IEEE80211B:
		basic_rates = basic_rates_b;
		break;
	case HOSTAPD_MODE_IEEE80211G:
		basic_rates = basic_rates_g;
		break;
	case HOSTAPD_MODE_IEEE80211AD:
		return 0; /* No basic rates for 11ad */
	default:
		return -1;
	}

	i = 0;
	while (basic_rates[i] >= 0)
		i++;
	if (i)
		i++; /* -1 termination */
	os_free(iface->basic_rates);
	iface->basic_rates = os_malloc(i * sizeof(int));
	if (iface->basic_rates)
		os_memcpy(iface->basic_rates, basic_rates, i * sizeof(int));

	os_free(iface->current_rates);
	iface->num_rates = 0;

	iface->current_rates =
		os_calloc(mode->num_rates, sizeof(struct hostapd_rate_data));
	if (!iface->current_rates) {
		wpa_printf(MSG_ERROR, "Failed to allocate memory for rate "
			   "table.");
		return -1;
	}

	for (i = 0; i < mode->num_rates; i++) {
		struct hostapd_rate_data *rate;

		if (iface->conf->supported_rates &&
		    !hostapd_rate_found(iface->conf->supported_rates,
					mode->rates[i]))
			continue;

		rate = &iface->current_rates[iface->num_rates];
		rate->rate = mode->rates[i];
		if (hostapd_rate_found(basic_rates, rate->rate)) {
			rate->flags |= HOSTAPD_RATE_BASIC;
			num_basic_rates++;
		}
		wpa_printf(MSG_DEBUG, "RATE[%d] rate=%d flags=0x%x",
			   iface->num_rates, rate->rate, rate->flags);
		iface->num_rates++;
	}

	if ((iface->num_rates == 0 || num_basic_rates == 0) &&
	    (!iface->conf->ieee80211n || !iface->conf->require_ht)) {
		wpa_printf(MSG_ERROR, "No rates remaining in supported/basic "
			   "rate sets (%d,%d).",
			   iface->num_rates, num_basic_rates);
		return -1;
	}

	return 0;
}