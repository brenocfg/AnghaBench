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
struct files_ref_store {int /*<<< orphan*/ * loose; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_ref_cache (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_loose_ref_cache(struct files_ref_store *refs)
{
	if (refs->loose) {
		free_ref_cache(refs->loose);
		refs->loose = NULL;
	}
}