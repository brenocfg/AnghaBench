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
struct futex_address {int /*<<< orphan*/  fa_key; } ;
typedef  int cloudabi_scope_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_SHARE ; 
#define  CLOUDABI_SCOPE_PRIVATE 129 
#define  CLOUDABI_SCOPE_SHARED 128 
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  THREAD_SHARE ; 
 int /*<<< orphan*/  TYPE_FUTEX ; 
 struct thread* curthread ; 
 int umtx_key_get (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
futex_address_create(struct futex_address *fa, struct thread *td,
    const void *object, cloudabi_scope_t scope)
{

	KASSERT(td == curthread,
	    ("Can only create umtx keys for the current thread"));
	switch (scope) {
	case CLOUDABI_SCOPE_PRIVATE:
		return (umtx_key_get(object, TYPE_FUTEX, THREAD_SHARE,
		    &fa->fa_key));
	case CLOUDABI_SCOPE_SHARED:
		return (umtx_key_get(object, TYPE_FUTEX, AUTO_SHARE,
		    &fa->fa_key));
	default:
		return (EINVAL);
	}
}