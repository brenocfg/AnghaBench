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

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  UMTX_OP_SHM ; 
 int /*<<< orphan*/  UMTX_SHM_DESTROY ; 
 int /*<<< orphan*/  _umtx_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pshared_clean(void *key, void *val)
{

	if (val != NULL)
		munmap(val, PAGE_SIZE);
	_umtx_op(NULL, UMTX_OP_SHM, UMTX_SHM_DESTROY, key, NULL);
}