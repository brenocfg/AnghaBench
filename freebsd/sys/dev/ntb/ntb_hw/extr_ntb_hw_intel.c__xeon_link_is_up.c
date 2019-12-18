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
struct ntb_softc {scalar_t__ conn_type; int lnk_sta; } ;

/* Variables and functions */
 scalar_t__ NTB_CONN_TRANSPARENT ; 
 int NTB_LINK_STATUS_ACTIVE ; 

__attribute__((used)) static inline bool
_xeon_link_is_up(struct ntb_softc *ntb)
{

	if (ntb->conn_type == NTB_CONN_TRANSPARENT)
		return (true);
	return ((ntb->lnk_sta & NTB_LINK_STATUS_ACTIVE) != 0);
}