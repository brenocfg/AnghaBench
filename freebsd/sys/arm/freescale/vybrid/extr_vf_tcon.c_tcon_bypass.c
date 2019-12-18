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
typedef  int uint32_t ;
struct tcon_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCON0_CTRL1 ; 
 int /*<<< orphan*/  TCON_BYPASS ; 
 int /*<<< orphan*/  WRITE4 (struct tcon_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcon_softc* tcon_sc ; 

uint32_t
tcon_bypass(void)
{
	struct tcon_softc *sc;

	if (tcon_sc == NULL)
		return (1);

	sc = tcon_sc;

	WRITE4(tcon_sc, TCON0_CTRL1, TCON_BYPASS);

	return (0);
}