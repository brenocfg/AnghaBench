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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ucom_softc {int dummy; } ;
struct termios {int /*<<< orphan*/  c_ospeed; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ umcs7840_calc_baudrate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
umcs7840_pre_param(struct ucom_softc *ucom, struct termios *t)
{
	uint8_t clk;
	uint16_t divisor;

	if (umcs7840_calc_baudrate(t->c_ospeed, &divisor, &clk) || !divisor)
		return (EINVAL);
	return (0);
}