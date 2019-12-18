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
struct __acl_aclcheck_link_args {int /*<<< orphan*/  aclp; int /*<<< orphan*/  type; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOFOLLOW ; 
 int kern___acl_aclcheck_path (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys___acl_aclcheck_link(struct thread *td, struct __acl_aclcheck_link_args *uap)
{
	return (kern___acl_aclcheck_path(td, uap->path, uap->type, uap->aclp,
	    NOFOLLOW));
}