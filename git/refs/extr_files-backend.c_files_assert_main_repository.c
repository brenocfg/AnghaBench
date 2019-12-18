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
struct files_ref_store {int store_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,char const*) ; 
 int REF_STORE_MAIN ; 

__attribute__((used)) static void files_assert_main_repository(struct files_ref_store *refs,
					 const char *caller)
{
	if (refs->store_flags & REF_STORE_MAIN)
		return;

	BUG("operation %s only allowed for main ref store", caller);
}