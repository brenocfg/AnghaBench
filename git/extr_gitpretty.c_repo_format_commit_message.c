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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;
struct pretty_print_context {char* output_encoding; } ;
struct format_commit_context {char const* commit_encoding; int /*<<< orphan*/  message; int /*<<< orphan*/  wrap_start; struct pretty_print_context const* pretty_ctx; struct commit const* commit; } ;
struct commit {int dummy; } ;
typedef  int /*<<< orphan*/  context ;

/* Variables and functions */
 int /*<<< orphan*/  format_commit_item ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memset (struct format_commit_context*,int /*<<< orphan*/ ,int) ; 
 char* reencode_string_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,size_t*) ; 
 int /*<<< orphan*/  repo_logmsg_reencode (struct repository*,struct commit const*,char const**,char const*) ; 
 int /*<<< orphan*/  repo_unuse_commit_buffer (struct repository*,struct commit const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewrap_message_tail (struct strbuf*,struct format_commit_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ same_encoding (char const*,char const*) ; 
 int /*<<< orphan*/  strbuf_attach (struct strbuf*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  strbuf_expand (struct strbuf*,char const*,int /*<<< orphan*/ ,struct format_commit_context*) ; 

void repo_format_commit_message(struct repository *r,
				const struct commit *commit,
				const char *format, struct strbuf *sb,
				const struct pretty_print_context *pretty_ctx)
{
	struct format_commit_context context;
	const char *output_enc = pretty_ctx->output_encoding;
	const char *utf8 = "UTF-8";

	memset(&context, 0, sizeof(context));
	context.commit = commit;
	context.pretty_ctx = pretty_ctx;
	context.wrap_start = sb->len;
	/*
	 * convert a commit message to UTF-8 first
	 * as far as 'format_commit_item' assumes it in UTF-8
	 */
	context.message = repo_logmsg_reencode(r, commit,
					       &context.commit_encoding,
					       utf8);

	strbuf_expand(sb, format, format_commit_item, &context);
	rewrap_message_tail(sb, &context, 0, 0, 0);

	/* then convert a commit message to an actual output encoding */
	if (output_enc) {
		if (same_encoding(utf8, output_enc))
			output_enc = NULL;
	} else {
		if (context.commit_encoding &&
		    !same_encoding(context.commit_encoding, utf8))
			output_enc = context.commit_encoding;
	}

	if (output_enc) {
		size_t outsz;
		char *out = reencode_string_len(sb->buf, sb->len,
						output_enc, utf8, &outsz);
		if (out)
			strbuf_attach(sb, out, outsz, outsz + 1);
	}

	free(context.commit_encoding);
	repo_unuse_commit_buffer(r, commit, context.message);
}