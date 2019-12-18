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
typedef  int uint64_t ;
typedef  scalar_t__ u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,scalar_t__,int) ; 

__attribute__((used)) static __inline void
ahd_outq(struct ahd_softc *ahd, u_int port, uint64_t value)
{
	ahd_outb(ahd, port, value & 0xFF);
	ahd_outb(ahd, port+1, (value >> 8) & 0xFF);
	ahd_outb(ahd, port+2, (value >> 16) & 0xFF);
	ahd_outb(ahd, port+3, (value >> 24) & 0xFF);
	ahd_outb(ahd, port+4, (value >> 32) & 0xFF);
	ahd_outb(ahd, port+5, (value >> 40) & 0xFF);
	ahd_outb(ahd, port+6, (value >> 48) & 0xFF);
	ahd_outb(ahd, port+7, (value >> 56) & 0xFF);
}