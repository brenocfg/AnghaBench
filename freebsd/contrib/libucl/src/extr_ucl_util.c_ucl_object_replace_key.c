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
typedef  int /*<<< orphan*/  ucl_object_t ;

/* Variables and functions */
 int ucl_object_insert_key_common (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,size_t,int,int,int) ; 

bool
ucl_object_replace_key (ucl_object_t *top, ucl_object_t *elt,
		const char *key, size_t keylen, bool copy_key)
{
	return ucl_object_insert_key_common (top, elt, key, keylen, copy_key, false, true);
}