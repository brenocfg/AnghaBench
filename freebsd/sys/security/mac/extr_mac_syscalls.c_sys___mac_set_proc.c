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
struct __mac_set_proc_args {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

int
sys___mac_set_proc(struct thread *td, struct __mac_set_proc_args *uap)
{

	return (ENOSYS);
}