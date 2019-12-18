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
struct object_id {int dummy; } ;

/* Variables and functions */
 char* oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static int list_each_note(const struct object_id *object_oid,
		const struct object_id *note_oid, char *note_path,
		void *cb_data)
{
	printf("%s %s\n", oid_to_hex(note_oid), oid_to_hex(object_oid));
	return 0;
}