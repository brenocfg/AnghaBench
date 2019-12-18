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
 int /*<<< orphan*/  strlen (char const*) ; 
 int ucl_object_delete_keyl (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

bool
ucl_object_delete_key (ucl_object_t *top, const char *key)
{
	return ucl_object_delete_keyl (top, key, strlen (key));
}