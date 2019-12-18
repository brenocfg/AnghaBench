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
struct ntb_softc {int lnk_sta; } ;
typedef  enum ntb_speed { ____Placeholder_ntb_speed } ntb_speed ;

/* Variables and functions */
 int NTB_LINK_SPEED_MASK ; 
 int NTB_SPEED_NONE ; 
 int /*<<< orphan*/  link_is_up (struct ntb_softc*) ; 

__attribute__((used)) static inline enum ntb_speed
intel_ntb_link_sta_speed(struct ntb_softc *ntb)
{

	if (!link_is_up(ntb))
		return (NTB_SPEED_NONE);
	return (ntb->lnk_sta & NTB_LINK_SPEED_MASK);
}