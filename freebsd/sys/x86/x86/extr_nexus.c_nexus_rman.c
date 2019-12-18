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
struct rman {int dummy; } ;

/* Variables and functions */
#define  SYS_RES_DRQ 131 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 struct rman drq_rman ; 
 struct rman irq_rman ; 
 struct rman mem_rman ; 
 struct rman port_rman ; 

__attribute__((used)) static struct rman *
nexus_rman(int type)
{
	switch (type) {
	case SYS_RES_IRQ:
		return (&irq_rman);
	case SYS_RES_DRQ:
		return (&drq_rman);
	case SYS_RES_IOPORT:
		return (&port_rman);
	case SYS_RES_MEMORY:
		return (&mem_rman);
	default:
		return (NULL);
	}
}