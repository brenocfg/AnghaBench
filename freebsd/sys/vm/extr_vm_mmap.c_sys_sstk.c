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
struct thread {int dummy; } ;
struct sstk_args {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

int
sys_sstk(struct thread *td, struct sstk_args *uap)
{
	/* Not yet implemented */
	return (EOPNOTSUPP);
}