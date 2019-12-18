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

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  head_oid ; 
 int /*<<< orphan*/  merge_head_oid ; 
 scalar_t__ read_ref (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void read_head_pointers(void)
{
	if (read_ref("HEAD", &head_oid))
		die("No HEAD -- no initial commit yet?");
	if (read_ref("MERGE_HEAD", &merge_head_oid)) {
		fprintf(stderr, "Not in the middle of a merge.\n");
		exit(0);
	}
}