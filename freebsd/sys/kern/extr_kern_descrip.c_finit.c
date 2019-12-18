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
struct fileops {int dummy; } ;
struct file {short f_type; int /*<<< orphan*/  f_ops; int /*<<< orphan*/  f_flag; void* f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_store_rel_ptr (uintptr_t volatile*,uintptr_t) ; 

void
finit(struct file *fp, u_int flag, short type, void *data, struct fileops *ops)
{
	fp->f_data = data;
	fp->f_flag = flag;
	fp->f_type = type;
	atomic_store_rel_ptr((volatile uintptr_t *)&fp->f_ops, (uintptr_t)ops);
}