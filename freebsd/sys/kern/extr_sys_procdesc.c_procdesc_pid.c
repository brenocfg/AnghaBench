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
struct procdesc {int /*<<< orphan*/  pd_pid; } ;
struct file {scalar_t__ f_type; struct procdesc* f_data; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 scalar_t__ DTYPE_PROCDESC ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

pid_t
procdesc_pid(struct file *fp_procdesc)
{
	struct procdesc *pd;

	KASSERT(fp_procdesc->f_type == DTYPE_PROCDESC,
	   ("procdesc_pid: !procdesc"));

	pd = fp_procdesc->f_data;
	return (pd->pd_pid);
}