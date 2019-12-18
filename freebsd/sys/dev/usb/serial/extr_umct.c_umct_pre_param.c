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
struct ucom_softc {int dummy; } ;
struct termios {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
umct_pre_param(struct ucom_softc *ucom, struct termios *t)
{
	return (0);			/* we accept anything */
}