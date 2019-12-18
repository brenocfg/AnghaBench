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
typedef  int u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int,int) ; 

__attribute__((used)) static __inline void
ahd_outw(struct ahd_softc *ahd, u_int port, u_int value)
{
	/*
	 * Write low byte first to accommodate registers
	 * such as PRGMCNT where the order maters.
	 */
	ahd_outb(ahd, port, value & 0xFF);
	ahd_outb(ahd, port+1, (value >> 8) & 0xFF);
}