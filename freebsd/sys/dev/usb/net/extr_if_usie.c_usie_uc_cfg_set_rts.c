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
typedef  scalar_t__ uint8_t ;
struct ucom_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ USIE_LS_RTS ; 
 int /*<<< orphan*/  usie_uc_update_line_state (struct ucom_softc*,scalar_t__) ; 

__attribute__((used)) static void
usie_uc_cfg_set_rts(struct ucom_softc *ucom, uint8_t flag)
{
	uint8_t rts;

	rts = flag ? USIE_LS_RTS : 0;
	usie_uc_update_line_state(ucom, rts);
}