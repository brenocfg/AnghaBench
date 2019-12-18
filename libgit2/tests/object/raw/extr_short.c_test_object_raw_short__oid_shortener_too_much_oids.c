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
 scalar_t__ MAX_OIDS ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  free_oids (scalar_t__,char**) ; 
 int /*<<< orphan*/  git_oid_shorten_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_oid_shorten_new (int /*<<< orphan*/ ) ; 
 scalar_t__ insert_sequential_oids (char***,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

void test_object_raw_short__oid_shortener_too_much_oids(void)
{
    /* The magic number of oids at which an oid_shortener will fail.
     * This was experimentally established. */
#define MAX_OIDS 24556

	git_oid_shorten *os;
	char **oids;

	os = git_oid_shorten_new(0);
	cl_assert(os != NULL);

	cl_assert(insert_sequential_oids(&oids, os, MAX_OIDS, MAX_OIDS - 1) < 0);

	free_oids(MAX_OIDS, oids);
	git_oid_shorten_free(os);

#undef MAX_OIDS
}