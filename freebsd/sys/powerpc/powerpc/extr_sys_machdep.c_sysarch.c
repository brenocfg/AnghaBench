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
struct sysarch_args {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

int
sysarch(struct thread *td, struct sysarch_args *uap)
{

	return (EINVAL);
}