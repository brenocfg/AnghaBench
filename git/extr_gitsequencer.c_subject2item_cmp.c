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
struct subject2item_entry {void const* subject; } ;

/* Variables and functions */
 int strcmp (void const*,void const*) ; 

__attribute__((used)) static int subject2item_cmp(const void *fndata,
			    const struct subject2item_entry *a,
			    const struct subject2item_entry *b, const void *key)
{
	return key ? strcmp(a->subject, key) : strcmp(a->subject, b->subject);
}