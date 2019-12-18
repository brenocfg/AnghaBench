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
struct usb2_clock_sel_priv {scalar_t__ base; int /*<<< orphan*/  xtal; scalar_t__ extal; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKSET0_PRIVATE ; 
 scalar_t__ USB20_CLKSET0 ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void usb2_clock_sel_disable_extal_only(struct usb2_clock_sel_priv *priv)
{
	if (priv->extal && !priv->xtal)
		writew(CLKSET0_PRIVATE, priv->base + USB20_CLKSET0);
}