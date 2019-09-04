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
struct conf_info {void* command; void* key; void* name; } ;

/* Variables and functions */
 void* xstrdup_or_null (void*) ; 

__attribute__((used)) static void duplicate_conf(struct conf_info *dst, const struct conf_info *src)
{
	*dst = *src;
	dst->name = xstrdup_or_null(src->name);
	dst->key = xstrdup_or_null(src->key);
	dst->command = xstrdup_or_null(src->command);
}