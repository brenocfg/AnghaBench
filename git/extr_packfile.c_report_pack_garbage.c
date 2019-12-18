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
struct string_list {int nr; TYPE_1__* items; } ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKDIR_FILE_GARBAGE ; 
 int /*<<< orphan*/  report_garbage (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  report_helper (struct string_list*,int,int,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_list_sort (struct string_list*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static void report_pack_garbage(struct string_list *list)
{
	int i, baselen = -1, first = 0, seen_bits = 0;

	if (!report_garbage)
		return;

	string_list_sort(list);

	for (i = 0; i < list->nr; i++) {
		const char *path = list->items[i].string;
		if (baselen != -1 &&
		    strncmp(path, list->items[first].string, baselen)) {
			report_helper(list, seen_bits, first, i);
			baselen = -1;
			seen_bits = 0;
		}
		if (baselen == -1) {
			const char *dot = strrchr(path, '.');
			if (!dot) {
				report_garbage(PACKDIR_FILE_GARBAGE, path);
				continue;
			}
			baselen = dot - path + 1;
			first = i;
		}
		if (!strcmp(path + baselen, "pack"))
			seen_bits |= 1;
		else if (!strcmp(path + baselen, "idx"))
			seen_bits |= 2;
	}
	report_helper(list, seen_bits, first, list->nr);
}