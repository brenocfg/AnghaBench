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
typedef  int uint32_t ;
struct bhnd_softc {int dummy; } ;
struct bhnd_core_clkctl {int /*<<< orphan*/  cc_dev; } ;
typedef  scalar_t__ device_t ;
typedef  int bhnd_clock ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_ASSERT_CLKCTL_AVAIL (struct bhnd_core_clkctl*) ; 
 int BHND_CCS_ALPAVAIL ; 
 int BHND_CCS_FORCEALP ; 
 int BHND_CCS_FORCEHT ; 
 int BHND_CCS_FORCEILP ; 
 int /*<<< orphan*/  BHND_CCS_FORCE_MASK ; 
 int BHND_CCS_HTAVAIL ; 
 int /*<<< orphan*/  BHND_CLKCTL_LOCK (struct bhnd_core_clkctl*) ; 
 int /*<<< orphan*/  BHND_CLKCTL_SET_4 (struct bhnd_core_clkctl*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_CLKCTL_UNLOCK (struct bhnd_core_clkctl*) ; 
#define  BHND_CLOCK_ALP 131 
#define  BHND_CLOCK_DYN 130 
#define  BHND_CLOCK_HT 129 
#define  BHND_CLOCK_ILP 128 
 int EINVAL ; 
 int ENODEV ; 
 int bhnd_core_clkctl_wait (struct bhnd_core_clkctl*,int,int) ; 
 struct bhnd_core_clkctl* bhnd_get_pmu_info (scalar_t__) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct bhnd_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
bhnd_generic_request_clock(device_t dev, device_t child, bhnd_clock clock)
{
	struct bhnd_softc	*sc;
	struct bhnd_core_clkctl	*clkctl;
	uint32_t		 avail;
	uint32_t		 req;
	int			 error;

	sc = device_get_softc(dev);

	if (device_get_parent(child) != dev)
		return (EINVAL);

	if ((clkctl = bhnd_get_pmu_info(child)) == NULL)
		panic("no active PMU allocation");

	BHND_ASSERT_CLKCTL_AVAIL(clkctl);

	avail = 0x0;
	req = 0x0;

	switch (clock) {
	case BHND_CLOCK_DYN:
		break;
	case BHND_CLOCK_ILP:
		req |= BHND_CCS_FORCEILP;
		break;
	case BHND_CLOCK_ALP:
		req |= BHND_CCS_FORCEALP;
		avail |= BHND_CCS_ALPAVAIL;
		break;
	case BHND_CLOCK_HT:
		req |= BHND_CCS_FORCEHT;
		avail |= BHND_CCS_HTAVAIL;
		break;
	default:
		device_printf(dev, "%s requested unknown clock: %#x\n",
		    device_get_nameunit(clkctl->cc_dev), clock);
		return (ENODEV);
	}

	BHND_CLKCTL_LOCK(clkctl);

	/* Issue request */
	BHND_CLKCTL_SET_4(clkctl, req, BHND_CCS_FORCE_MASK);

	/* Wait for clock availability */
	error = bhnd_core_clkctl_wait(clkctl, avail, avail);

	BHND_CLKCTL_UNLOCK(clkctl);

	return (error);
}