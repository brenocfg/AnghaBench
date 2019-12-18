#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {TYPE_1__* items; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int PACKDIR_FILE_IDX ; 
 int PACKDIR_FILE_PACK ; 
 int /*<<< orphan*/  report_garbage (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void report_helper(const struct string_list *list,
			  int seen_bits, int first, int last)
{
	if (seen_bits == (PACKDIR_FILE_PACK|PACKDIR_FILE_IDX))
		return;

	for (; first < last; first++)
		report_garbage(seen_bits, list->items[first].string);
}