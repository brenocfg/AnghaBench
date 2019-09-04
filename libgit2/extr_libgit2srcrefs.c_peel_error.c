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
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int peel_error(int error, const git_reference *ref, const char* msg)
{
	git_error_set(
		GIT_ERROR_INVALID,
		"the reference '%s' cannot be peeled - %s", git_reference_name(ref), msg);
	return error;
}