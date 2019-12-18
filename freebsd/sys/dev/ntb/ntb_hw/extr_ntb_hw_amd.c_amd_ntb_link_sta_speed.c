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
struct amd_ntb_softc {int /*<<< orphan*/  lnk_sta; } ;
typedef  enum ntb_speed { ____Placeholder_ntb_speed } ntb_speed ;

/* Variables and functions */
 int NTB_LNK_STA_SPEED (int /*<<< orphan*/ ) ; 
 int NTB_SPEED_NONE ; 
 int /*<<< orphan*/  amd_link_is_up (struct amd_ntb_softc*) ; 

__attribute__((used)) static inline enum ntb_speed
amd_ntb_link_sta_speed(struct amd_ntb_softc *ntb)
{

	if (!amd_link_is_up(ntb))
		return (NTB_SPEED_NONE);

	return (NTB_LNK_STA_SPEED(ntb->lnk_sta));
}