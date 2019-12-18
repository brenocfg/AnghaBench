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
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ key_cnt ; 
 int /*<<< orphan*/ * key_ptr ; 
 scalar_t__ restoreKeyDb ; 
 int /*<<< orphan*/  sntptest_destroy () ; 

void
tearDown(void)
{	
	if (restoreKeyDb) {
		key_cnt = 0;
		free(key_ptr);
		key_ptr = NULL;
	}

	sntptest_destroy(); /* only on the final test!! if counter == 0 etc... */
}