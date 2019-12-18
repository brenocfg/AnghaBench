#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct split_index {scalar_t__ delete_bitmap; scalar_t__ replace_bitmap; int /*<<< orphan*/  base_oid; } ;
struct cache_entry {int ce_mode; char* name; int /*<<< orphan*/  oid; } ;
struct TYPE_3__ {int cache_nr; struct cache_entry** cache; struct split_index* split_index; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int ce_stage (struct cache_entry*) ; 
 int /*<<< orphan*/  do_read_index (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  ewah_each_bit (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  show_bit ; 
 TYPE_1__ the_index ; 

int cmd__dump_split_index(int ac, const char **av)
{
	struct split_index *si;
	int i;

	do_read_index(&the_index, av[1], 1);
	printf("own %s\n", oid_to_hex(&the_index.oid));
	si = the_index.split_index;
	if (!si) {
		printf("not a split index\n");
		return 0;
	}
	printf("base %s\n", oid_to_hex(&si->base_oid));
	for (i = 0; i < the_index.cache_nr; i++) {
		struct cache_entry *ce = the_index.cache[i];
		printf("%06o %s %d\t%s\n", ce->ce_mode,
		       oid_to_hex(&ce->oid), ce_stage(ce), ce->name);
	}
	printf("replacements:");
	if (si->replace_bitmap)
		ewah_each_bit(si->replace_bitmap, show_bit, NULL);
	printf("\ndeletions:");
	if (si->delete_bitmap)
		ewah_each_bit(si->delete_bitmap, show_bit, NULL);
	printf("\n");
	return 0;
}