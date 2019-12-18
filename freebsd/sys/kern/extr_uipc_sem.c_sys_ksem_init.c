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
struct ksem_init_args {int /*<<< orphan*/  value; int /*<<< orphan*/  idp; } ;

/* Variables and functions */
 int S_IRWXG ; 
 int S_IRWXU ; 
 int ksem_create (struct thread*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_ksem_init(struct thread *td, struct ksem_init_args *uap)
{

	return (ksem_create(td, NULL, uap->idp, S_IRWXU | S_IRWXG, uap->value,
	    0, 0));
}