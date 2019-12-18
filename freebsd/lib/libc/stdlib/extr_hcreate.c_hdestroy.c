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
 int /*<<< orphan*/  global_hashtable ; 
 int global_hashtable_initialized ; 
 int /*<<< orphan*/  hdestroy_r (int /*<<< orphan*/ *) ; 

void
hdestroy(void)
{

	/* Destroy global hash table if present. */
	if (global_hashtable_initialized) {
		hdestroy_r(&global_hashtable);
		global_hashtable_initialized = false;
	}
}