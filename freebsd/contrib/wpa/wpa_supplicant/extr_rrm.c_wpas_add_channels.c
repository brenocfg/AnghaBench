#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct oper_class_map {int max_chan; int min_chan; int inc; scalar_t__ bw; int /*<<< orphan*/  op_class; } ;
struct hostapd_hw_modes {int dummy; } ;
typedef  enum chan_allowed { ____Placeholder_chan_allowed } chan_allowed ;

/* Variables and functions */
 scalar_t__ BW160 ; 
 scalar_t__ BW80 ; 
 scalar_t__ BW80P80 ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int NOT_ALLOWED ; 
 int NO_IR ; 
 int* os_calloc (int,int) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int verify_channel (struct hostapd_hw_modes*,int,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpas_add_channel (int /*<<< orphan*/ ,int,int,int*) ; 

__attribute__((used)) static int * wpas_add_channels(const struct oper_class_map *op,
			       struct hostapd_hw_modes *mode, int active,
			       const u8 *channels, const u8 size)
{
	int *freqs, *next_freq;
	u8 num_primary_channels, i;
	u8 num_chans;

	num_chans = channels ? size :
		(op->max_chan - op->min_chan) / op->inc + 1;

	if (op->bw == BW80 || op->bw == BW80P80)
		num_primary_channels = 4;
	else if (op->bw == BW160)
		num_primary_channels = 8;
	else
		num_primary_channels = 1;

	/* one extra place for the zero-terminator */
	freqs = os_calloc(num_chans * num_primary_channels + 1, sizeof(*freqs));
	if (!freqs) {
		wpa_printf(MSG_ERROR,
			   "Beacon Report: Failed to allocate freqs array");
		return NULL;
	}

	next_freq = freqs;
	for  (i = 0; i < num_chans; i++) {
		u8 chan = channels ? channels[i] : op->min_chan + i * op->inc;
		enum chan_allowed res = verify_channel(mode, chan, op->bw);

		if (res == NOT_ALLOWED || (res == NO_IR && active))
			continue;

		if (wpas_add_channel(op->op_class, chan, num_primary_channels,
				     next_freq) < 0) {
			os_free(freqs);
			return NULL;
		}

		next_freq += num_primary_channels;
	}

	if (!freqs[0]) {
		os_free(freqs);
		return NULL;
	}

	return freqs;
}