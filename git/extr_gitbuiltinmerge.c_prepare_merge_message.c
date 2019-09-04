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
struct strbuf {scalar_t__ len; } ;
struct fmt_merge_msg_opts {int add_title; int credit_people; int /*<<< orphan*/  shortlog_len; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 int /*<<< orphan*/  fmt_merge_msg (struct strbuf*,struct strbuf*,struct fmt_merge_msg_opts*) ; 
 int /*<<< orphan*/  have_message ; 
 int /*<<< orphan*/  memset (struct fmt_merge_msg_opts*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ option_edit ; 
 int /*<<< orphan*/  shortlog_len ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,scalar_t__) ; 

__attribute__((used)) static void prepare_merge_message(struct strbuf *merge_names, struct strbuf *merge_msg)
{
	struct fmt_merge_msg_opts opts;

	memset(&opts, 0, sizeof(opts));
	opts.add_title = !have_message;
	opts.shortlog_len = shortlog_len;
	opts.credit_people = (0 < option_edit);

	fmt_merge_msg(merge_names, merge_msg, &opts);
	if (merge_msg->len)
		strbuf_setlen(merge_msg, merge_msg->len - 1);
}