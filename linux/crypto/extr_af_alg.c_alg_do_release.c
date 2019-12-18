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
struct af_alg_type {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* release ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void alg_do_release(const struct af_alg_type *type, void *private)
{
	if (!type)
		return;

	type->release(private);
	module_put(type->owner);
}