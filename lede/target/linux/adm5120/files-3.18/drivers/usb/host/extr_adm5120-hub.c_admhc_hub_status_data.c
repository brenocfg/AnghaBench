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
typedef  int u32 ;
struct usb_hcd {int /*<<< orphan*/  flags; } ;
struct admhcd {int num_ports; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ADMHC_PS_CCS ; 
 int ADMHC_PS_CSC ; 
 int ADMHC_PS_OCIC ; 
 int ADMHC_PS_PESC ; 
 int ADMHC_PS_PRSC ; 
 int ADMHC_PS_PSSC ; 
 int ADMHC_RH_LPSC ; 
 int ADMHC_RH_OCIC ; 
 int /*<<< orphan*/  HCD_FLAG_POLL_RH ; 
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (struct usb_hcd*) ; 
 int admhc_read_portstatus (struct admhcd*,int) ; 
 int admhc_read_rhdesc (struct admhcd*) ; 
 scalar_t__ admhc_root_hub_state_changes (struct admhcd*,int,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct admhcd* hcd_to_admhcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
admhc_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	struct admhcd	*ahcd = hcd_to_admhcd(hcd);
	int		i, changed = 0, length = 1;
	int		any_connected = 0;
	unsigned long	flags;
	u32		status;

	spin_lock_irqsave(&ahcd->lock, flags);
	if (!HCD_HW_ACCESSIBLE(hcd))
		goto done;

	/* init status */
	status = admhc_read_rhdesc(ahcd);
	if (status & (ADMHC_RH_LPSC | ADMHC_RH_OCIC))
		buf[0] = changed = 1;
	else
		buf[0] = 0;
	if (ahcd->num_ports > 7) {
		buf[1] = 0;
		length++;
	}

	/* look at each port */
	for (i = 0; i < ahcd->num_ports; i++) {
		status = admhc_read_portstatus(ahcd, i);

		/* can't autostop if ports are connected */
		any_connected |= (status & ADMHC_PS_CCS);

		if (status & (ADMHC_PS_CSC | ADMHC_PS_PESC | ADMHC_PS_PSSC
				| ADMHC_PS_OCIC | ADMHC_PS_PRSC)) {
			changed = 1;
			if (i < 7)
				buf[0] |= 1 << (i + 1);
			else
				buf[1] |= 1 << (i - 7);
		}
	}

	if (admhc_root_hub_state_changes(ahcd, changed,
			any_connected))
		set_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	else
		clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);

done:
	spin_unlock_irqrestore(&ahcd->lock, flags);

	return changed ? length : 0;
}