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
struct ntb_softc {int /*<<< orphan*/  lnk_sta; } ;
typedef  enum ntb_width { ____Placeholder_ntb_width } ntb_width ;

/* Variables and functions */
 int NTB_LNK_STA_WIDTH (int /*<<< orphan*/ ) ; 
 int NTB_WIDTH_NONE ; 
 int /*<<< orphan*/  link_is_up (struct ntb_softc*) ; 

__attribute__((used)) static inline enum ntb_width
intel_ntb_link_sta_width(struct ntb_softc *ntb)
{

	if (!link_is_up(ntb))
		return (NTB_WIDTH_NONE);
	return (NTB_LNK_STA_WIDTH(ntb->lnk_sta));
}