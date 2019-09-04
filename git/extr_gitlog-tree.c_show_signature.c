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
struct strbuf {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct rev_info {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ parse_signed_commit (struct commit*,struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  show_sig_lines (struct rev_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int verify_signed_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void show_signature(struct rev_info *opt, struct commit *commit)
{
	struct strbuf payload = STRBUF_INIT;
	struct strbuf signature = STRBUF_INIT;
	struct strbuf gpg_output = STRBUF_INIT;
	int status;

	if (parse_signed_commit(commit, &payload, &signature) <= 0)
		goto out;

	status = verify_signed_buffer(payload.buf, payload.len,
				      signature.buf, signature.len,
				      &gpg_output, NULL);
	if (status && !gpg_output.len)
		strbuf_addstr(&gpg_output, "No signature\n");

	show_sig_lines(opt, status, gpg_output.buf);

 out:
	strbuf_release(&gpg_output);
	strbuf_release(&payload);
	strbuf_release(&signature);
}