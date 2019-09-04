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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_new (int /*<<< orphan*/ *,char*,char*,int,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  signature ; 

void test_stash_drop__initialize(void)
{
	cl_git_pass(git_repository_init(&repo, "stash", 0));
	cl_git_pass(git_signature_new(&signature, "nulltoken", "emeric.fermas@gmail.com", 1323847743, 60)); /* Wed Dec 14 08:29:03 2011 +0100 */
}