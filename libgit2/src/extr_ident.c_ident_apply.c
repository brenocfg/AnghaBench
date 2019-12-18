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
typedef  void* git_filter ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 scalar_t__ GIT_FILTER_SMUDGE ; 
 int GIT_PASSTHROUGH ; 
 int /*<<< orphan*/  GIT_UNUSED (void**) ; 
 scalar_t__ git_buf_text_is_binary (int /*<<< orphan*/  const*) ; 
 scalar_t__ git_filter_source_mode (int /*<<< orphan*/  const*) ; 
 int ident_insert_id (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int ident_remove_id (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int ident_apply(
	git_filter     *self,
	void          **payload,
	git_buf        *to,
	const git_buf  *from,
	const git_filter_source *src)
{
	GIT_UNUSED(self); GIT_UNUSED(payload);

	/* Don't filter binary files */
	if (git_buf_text_is_binary(from))
		return GIT_PASSTHROUGH;

	if (git_filter_source_mode(src) == GIT_FILTER_SMUDGE)
		return ident_insert_id(to, from, src);
	else
		return ident_remove_id(to, from);
}