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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  base_t ;

/* Variables and functions */
 void* base_alloc_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ *) ; 

void *
base_alloc(tsdn_t *tsdn, base_t *base, size_t size, size_t alignment) {
	return base_alloc_impl(tsdn, base, size, alignment, NULL);
}