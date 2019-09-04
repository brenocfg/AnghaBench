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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 char* oid_to_hex (struct object_id const*) ; 

__attribute__((used)) static int write_packed_entry(FILE *fh, const char *refname,
			      const struct object_id *oid,
			      const struct object_id *peeled)
{
	if (fprintf(fh, "%s %s\n", oid_to_hex(oid), refname) < 0 ||
	    (peeled && fprintf(fh, "^%s\n", oid_to_hex(peeled)) < 0))
		return -1;

	return 0;
}