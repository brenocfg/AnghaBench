#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ isc_prefix_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  isc_refcount_decrement (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  isc_refcount_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_deref_prefix(isc_mem_t *mctx, isc_prefix_t *prefix) {
	int refs;

	if (prefix == NULL)
		return;

	isc_refcount_decrement(&prefix->refcount, &refs);

	if (refs <= 0) {
		isc_refcount_destroy(&prefix->refcount);
		isc_mem_put(mctx, prefix, sizeof(isc_prefix_t));
	}
}