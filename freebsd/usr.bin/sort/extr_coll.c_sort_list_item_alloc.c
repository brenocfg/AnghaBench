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
struct sort_list_item {int dummy; } ;

/* Variables and functions */
 int keys_array_size () ; 
 int /*<<< orphan*/  memset (struct sort_list_item*,int /*<<< orphan*/ ,size_t) ; 
 struct sort_list_item* sort_malloc (size_t) ; 

struct sort_list_item *
sort_list_item_alloc(void)
{
	struct sort_list_item *si;
	size_t sz;

	sz = sizeof(struct sort_list_item) + keys_array_size();
	si = sort_malloc(sz);
	memset(si, 0, sz);

	return (si);
}