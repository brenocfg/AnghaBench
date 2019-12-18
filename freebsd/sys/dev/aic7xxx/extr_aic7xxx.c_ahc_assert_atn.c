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
typedef  int /*<<< orphan*/  u_int ;
struct ahc_softc {int features; } ;

/* Variables and functions */
 int AHC_DT ; 
 int /*<<< orphan*/  ATNO ; 
 int /*<<< orphan*/  SCSISIGI ; 
 int /*<<< orphan*/  SCSISIGO ; 
 int /*<<< orphan*/  ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahc_assert_atn(struct ahc_softc *ahc)
{
	u_int scsisigo;

	scsisigo = ATNO;
	if ((ahc->features & AHC_DT) == 0)
		scsisigo |= ahc_inb(ahc, SCSISIGI);
	ahc_outb(ahc, SCSISIGO, scsisigo);
}