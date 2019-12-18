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
struct uchcom_divider {int dummy; } ;
struct termios {int c_cflag; int /*<<< orphan*/  c_ospeed; } ;

/* Variables and functions */
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int EIO ; 
 int PARENB ; 
 scalar_t__ uchcom_calc_divider_settings (struct uchcom_divider*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uchcom_pre_param(struct ucom_softc *ucom, struct termios *t)
{
	struct uchcom_divider dv;

	switch (t->c_cflag & CSIZE) {
	case CS8:
		break;
	default:
		return (EIO);
	}
	if ((t->c_cflag & CSTOPB) != 0)
		return (EIO);
	if ((t->c_cflag & PARENB) != 0)
		return (EIO);

	if (uchcom_calc_divider_settings(&dv, t->c_ospeed)) {
		return (EIO);
	}
	return (0);			/* success */
}