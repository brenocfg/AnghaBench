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
typedef  int /*<<< orphan*/  git_filter_source ;
typedef  int /*<<< orphan*/  git_filter ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_PASSTHROUGH ; 
 int bitflip_filter_apply (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cl_fail (char*) ; 
 int reverse_filter_apply (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int wildcard_filter_apply(
	git_filter     *self,
	void          **payload,
	git_buf        *to,
	const git_buf  *from,
	const git_filter_source *source)
{
	const char *filtername = *payload;

	if (filtername && strcmp(filtername, "wcflip") == 0)
		return bitflip_filter_apply(self, payload, to, from, source);
	else if (filtername && strcmp(filtername, "wcreverse") == 0)
		return reverse_filter_apply(self, payload, to, from, source);

	cl_fail("Unexpected attribute");
	return GIT_PASSTHROUGH;
}