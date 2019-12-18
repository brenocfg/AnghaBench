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
typedef  int u_int ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int MAXCPU ; 
 int /*<<< orphan*/  MPIC_SOFT_INT ; 
 int /*<<< orphan*/  MPIC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_mpic_sc ; 

void
mpic_ipi_send(device_t dev, struct intr_irqsrc *isrc, cpuset_t cpus, u_int ipi)
{
	uint32_t val, i;

	val = 0x00000000;
	for (i = 0; i < MAXCPU; i++)
		if (CPU_ISSET(i, &cpus))
			val |= (1 << (8 + i));
	val |= ipi;
	MPIC_WRITE(mv_mpic_sc, MPIC_SOFT_INT, val);
}