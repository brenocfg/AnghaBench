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
typedef  int /*<<< orphan*/  git_oid_shorten ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int git_oid_shorten_add (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_oid_shorten_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_oid_shorten_new (int /*<<< orphan*/ ) ; 

void test_object_raw_short__oid_shortener_no_duplicates(void)
{
	git_oid_shorten *os;
	int min_len;

	os = git_oid_shorten_new(0);
	cl_assert(os != NULL);

	git_oid_shorten_add(os, "22596363b3de40b06f981fb85d82312e8c0ed511");
	git_oid_shorten_add(os, "ce08fe4884650f067bd5703b6a59a8b3b3c99a09");
	git_oid_shorten_add(os, "16a0123456789abcdef4b775213c23a8bd74f5e0");
	min_len = git_oid_shorten_add(os, "ce08fe4884650f067bd5703b6a59a8b3b3c99a09");

	cl_assert(min_len == GIT_OID_HEXSZ + 1);

	git_oid_shorten_free(os);
}