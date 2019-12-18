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
struct amd_ntb_softc {int /*<<< orphan*/  hb_timer; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int AMD_LINK_HB_TIMEOUT ; 
 int /*<<< orphan*/  amd_link_is_up (struct amd_ntb_softc*) ; 
 scalar_t__ amd_ntb_poll_link (struct amd_ntb_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct amd_ntb_softc*) ; 
 int /*<<< orphan*/  ntb_link_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
amd_link_hb(void *arg)
{
	struct amd_ntb_softc *ntb = arg;

	if (amd_ntb_poll_link(ntb))
		ntb_link_event(ntb->device);

	if (!amd_link_is_up(ntb)) {
		callout_reset(&ntb->hb_timer, AMD_LINK_HB_TIMEOUT,
		    amd_link_hb, ntb);
	} else {
		callout_reset(&ntb->hb_timer, (AMD_LINK_HB_TIMEOUT * 10),
		    amd_link_hb, ntb);
	}
}