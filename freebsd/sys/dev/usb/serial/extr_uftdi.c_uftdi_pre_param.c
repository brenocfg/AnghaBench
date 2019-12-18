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
struct uftdi_param_config {int dummy; } ;
struct ucom_softc {int dummy; } ;
struct termios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int uftdi_set_parm_soft (struct ucom_softc*,struct termios*,struct uftdi_param_config*) ; 

__attribute__((used)) static int
uftdi_pre_param(struct ucom_softc *ucom, struct termios *t)
{
	struct uftdi_param_config cfg;

	DPRINTF("\n");

	return (uftdi_set_parm_soft(ucom, t, &cfg));
}