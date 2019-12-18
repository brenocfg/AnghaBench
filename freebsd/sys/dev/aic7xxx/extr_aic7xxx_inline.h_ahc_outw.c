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
struct ahc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int,int) ; 

__attribute__((used)) static __inline void
ahc_outw(struct ahc_softc *ahc, u_int port, u_int value)
{
	ahc_outb(ahc, port, value & 0xFF);
	ahc_outb(ahc, port+1, (value >> 8) & 0xFF);
}