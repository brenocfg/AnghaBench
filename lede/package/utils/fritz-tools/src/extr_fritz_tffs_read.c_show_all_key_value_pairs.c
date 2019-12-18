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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct tffs_key_name_table {int size; TYPE_1__* entries; } ;
struct tffs_entry {int dummy; } ;
struct TYPE_2__ {char* val; int /*<<< orphan*/ * id; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ find_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tffs_entry*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_entry_value (struct tffs_entry*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  to_entry_header_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int show_all_key_value_pairs(uint8_t *buffer,
				    struct tffs_key_name_table *key_names)
{
	int i, has_value = 0;
	uint16_t id;
	struct tffs_entry tmp;

	for (i = 0; i < key_names->size; i++) {
		id = to_entry_header_id(*key_names->entries[i].id);

		if (find_entry(buffer, id, &tmp)) {
			printf("%s=", key_names->entries[i].val);
			print_entry_value(&tmp);
			printf("\n");
			has_value++;
		}
	}

	if (!has_value) {
		fprintf(stderr, "ERROR: no values found!\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}