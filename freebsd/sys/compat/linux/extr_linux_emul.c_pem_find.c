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
struct proc {struct linux_pemuldata* p_emuldata; } ;
struct linux_pemuldata {int dummy; } ;

/* Variables and functions */

struct linux_pemuldata *
pem_find(struct proc *p)
{
	struct linux_pemuldata *pem;

	pem = p->p_emuldata;

	return (pem);
}