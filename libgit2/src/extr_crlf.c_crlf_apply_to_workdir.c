#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crlf_attrs {scalar_t__ crlf_action; } ;
struct TYPE_3__ {scalar_t__ lf; scalar_t__ crlf; scalar_t__ cr; } ;
typedef  TYPE_1__ git_buf_text_stats ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 scalar_t__ GIT_CRLF_AUTO ; 
 scalar_t__ GIT_CRLF_AUTO_CRLF ; 
 scalar_t__ GIT_CRLF_AUTO_INPUT ; 
 scalar_t__ GIT_EOL_CRLF ; 
 int GIT_PASSTHROUGH ; 
 scalar_t__ git_buf_len (int /*<<< orphan*/  const*) ; 
 int git_buf_text_gather_stats (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int git_buf_text_lf_to_crlf (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ output_eol (struct crlf_attrs*) ; 

__attribute__((used)) static int crlf_apply_to_workdir(
	struct crlf_attrs *ca,
	git_buf *to,
	const git_buf *from)
{
	git_buf_text_stats stats;
	bool is_binary;

	/* Empty file? Nothing to do. */
	if (git_buf_len(from) == 0 || output_eol(ca) != GIT_EOL_CRLF)
		return GIT_PASSTHROUGH;

	is_binary = git_buf_text_gather_stats(&stats, from, false);

	/* If there are no LFs, or all LFs are part of a CRLF, nothing to do */
	if (stats.lf == 0 || stats.lf == stats.crlf)
		return GIT_PASSTHROUGH;

	if (ca->crlf_action == GIT_CRLF_AUTO ||
		ca->crlf_action == GIT_CRLF_AUTO_INPUT ||
		ca->crlf_action == GIT_CRLF_AUTO_CRLF) {

		/* If we have any existing CR or CRLF line endings, do nothing */
		if (stats.cr > 0)
			return GIT_PASSTHROUGH;

		/* Don't filter binary files */
		if (is_binary)
			return GIT_PASSTHROUGH;
	}

	return git_buf_text_lf_to_crlf(to, from);
}