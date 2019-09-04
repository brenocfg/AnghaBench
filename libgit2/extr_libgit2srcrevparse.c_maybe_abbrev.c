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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int maybe_sha_or_abbrev (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int maybe_abbrev(git_object** out, git_repository *repo, const char *spec)
{
	size_t speclen = strlen(spec);

	return maybe_sha_or_abbrev(out, repo, spec, speclen);
}