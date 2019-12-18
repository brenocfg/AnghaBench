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
struct getauid_args {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

int
sys_getauid(struct thread *td, struct getauid_args *uap)
{

	return (ENOSYS);
}