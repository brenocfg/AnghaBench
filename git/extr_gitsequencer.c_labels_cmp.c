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
struct labels_entry {void const* label; } ;

/* Variables and functions */
 int strcmp (void const*,void const*) ; 

__attribute__((used)) static int labels_cmp(const void *fndata, const struct labels_entry *a,
		      const struct labels_entry *b, const void *key)
{
	return key ? strcmp(a->label, key) : strcmp(a->label, b->label);
}