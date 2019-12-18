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
struct commit_graft {int nr_parent; int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_one_shallow(const struct commit_graft *graft, void *cb_data)
{
	FILE *fp = cb_data;
	if (graft->nr_parent == -1)
		fprintf(fp, "--shallow %s\n", oid_to_hex(&graft->oid));
	return 0;
}