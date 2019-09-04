#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct commit_info {int /*<<< orphan*/  summary; int /*<<< orphan*/  committer_tz; int /*<<< orphan*/  committer_time; int /*<<< orphan*/  committer_mail; int /*<<< orphan*/  committer; int /*<<< orphan*/  author_tz; int /*<<< orphan*/  author_time; int /*<<< orphan*/  author_mail; int /*<<< orphan*/  author; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  commit_info_init (struct commit_info*) ; 
 int find_commit_subject (char const*,char const**) ; 
 int /*<<< orphan*/  get_ac_line (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* get_log_output_encoding () ; 
 char* logmsg_reencode (struct commit*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_add (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unuse_commit_buffer (struct commit*,char const*) ; 

__attribute__((used)) static void get_commit_info(struct commit *commit,
			    struct commit_info *ret,
			    int detailed)
{
	int len;
	const char *subject, *encoding;
	const char *message;

	commit_info_init(ret);

	encoding = get_log_output_encoding();
	message = logmsg_reencode(commit, NULL, encoding);
	get_ac_line(message, "\nauthor ",
		    &ret->author, &ret->author_mail,
		    &ret->author_time, &ret->author_tz);

	if (!detailed) {
		unuse_commit_buffer(commit, message);
		return;
	}

	get_ac_line(message, "\ncommitter ",
		    &ret->committer, &ret->committer_mail,
		    &ret->committer_time, &ret->committer_tz);

	len = find_commit_subject(message, &subject);
	if (len)
		strbuf_add(&ret->summary, subject, len);
	else
		strbuf_addf(&ret->summary, "(%s)", oid_to_hex(&commit->object.oid));

	unuse_commit_buffer(commit, message);
}