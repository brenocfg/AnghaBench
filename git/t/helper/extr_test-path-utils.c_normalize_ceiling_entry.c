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
struct string_list_item {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  is_absolute_path (char*) ; 
 scalar_t__ normalize_path_copy (char*,char*) ; 

__attribute__((used)) static int normalize_ceiling_entry(struct string_list_item *item, void *unused)
{
	char *ceil = item->string;

	if (!*ceil)
		die("Empty path is not supported");
	if (!is_absolute_path(ceil))
		die("Path \"%s\" is not absolute", ceil);
	if (normalize_path_copy(ceil, ceil) < 0)
		die("Path \"%s\" could not be normalized", ceil);
	return 1;
}