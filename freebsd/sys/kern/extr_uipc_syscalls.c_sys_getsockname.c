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
struct getsockname_args {int dummy; } ;

/* Variables and functions */
 int getsockname1 (struct thread*,struct getsockname_args*,int /*<<< orphan*/ ) ; 

int
sys_getsockname(struct thread *td, struct getsockname_args *uap)
{

	return (getsockname1(td, uap, 0));
}