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
 size_t MAX_OIDS ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_b (int,int) ; 
 int /*<<< orphan*/  free_oids (size_t,char**) ; 
 int /*<<< orphan*/  git_oid_shorten_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_oid_shorten_new (int /*<<< orphan*/ ) ; 
 int insert_sequential_oids (char***,int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

void test_object_raw_short__oid_shortener_stresstest_git_oid_shorten(void)
{
#define MAX_OIDS 1000

	git_oid_shorten *os;
	size_t i, j;
	int min_len = 0, found_collision;
	char **oids;

	os = git_oid_shorten_new(0);
	cl_assert(os != NULL);

	/*
	 * Insert in the shortener 1000 unique SHA1 ids
	 */
	min_len = insert_sequential_oids(&oids, os, MAX_OIDS, MAX_OIDS);
	cl_assert(min_len > 0);

	/*
	 * Compare the first `min_char - 1` characters of each
	 * SHA1 OID. If the minimizer worked, we should find at
	 * least one collision
	 */
	found_collision = 0;
	for (i = 0; i < MAX_OIDS; ++i) {
		for (j = i + 1; j < MAX_OIDS; ++j) {
			if (memcmp(oids[i], oids[j], min_len - 1) == 0)
				found_collision = 1;
		}
	}
	cl_assert_equal_b(true, found_collision);

	/*
	 * Compare the first `min_char` characters of each
	 * SHA1 OID. If the minimizer worked, every single preffix
	 * should be unique.
	 */
	found_collision = 0;
	for (i = 0; i < MAX_OIDS; ++i) {
		for (j = i + 1; j < MAX_OIDS; ++j) {
			if (memcmp(oids[i], oids[j], min_len) == 0)
				found_collision = 1;
		}
	}
	cl_assert_equal_b(false, found_collision);

	/* cleanup */
	free_oids(MAX_OIDS, oids);
	git_oid_shorten_free(os);

#undef MAX_OIDS
}