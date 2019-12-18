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
struct resource_list_entry {char const* start; int count; } ;
struct resource_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char const*,...) ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int,int) ; 

__attribute__((used)) static void
pccard_print_resources(struct resource_list *rl, const char *name, int type,
    int count, const char *format)
{
	struct resource_list_entry *rle;
	int printed;
	int i;

	printed = 0;
	for (i = 0; i < count; i++) {
		rle = resource_list_find(rl, type, i);
		if (rle != NULL) {
			if (printed == 0)
				printf(" %s ", name);
			else if (printed > 0)
				printf(",");
			printed++;
			printf(format, rle->start);
			if (rle->count > 1) {
				printf("-");
				printf(format, rle->start + rle->count - 1);
			}
		} else if (i > 3) {
			/* check the first few regardless */
			break;
		}
	}
}