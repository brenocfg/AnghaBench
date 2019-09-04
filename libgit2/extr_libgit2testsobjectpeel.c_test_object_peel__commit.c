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
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_OBJECT_TAG ; 
 int /*<<< orphan*/  GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  assert_peel (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_peel_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void test_object_peel__commit(void)
{
	assert_peel_error(GIT_EINVALIDSPEC, "e90810b8df3e80c413d903f631643c716887138d", GIT_OBJECT_BLOB);
	assert_peel("e90810b8df3e80c413d903f631643c716887138d", GIT_OBJECT_TREE,
		    "53fc32d17276939fc79ed05badaef2db09990016", GIT_OBJECT_TREE);
	assert_peel("e90810b8df3e80c413d903f631643c716887138d", GIT_OBJECT_COMMIT,
		    "e90810b8df3e80c413d903f631643c716887138d", GIT_OBJECT_COMMIT);
	assert_peel_error(GIT_EINVALIDSPEC, "e90810b8df3e80c413d903f631643c716887138d", GIT_OBJECT_TAG);
	assert_peel("e90810b8df3e80c413d903f631643c716887138d", GIT_OBJECT_ANY,
		    "53fc32d17276939fc79ed05badaef2db09990016", GIT_OBJECT_TREE);
}