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
struct commit_message {void* label; void* parent_label; int /*<<< orphan*/  subject; int /*<<< orphan*/  message; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int find_commit_subject (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  get_commit_output_encoding () ; 
 int /*<<< orphan*/  logmsg_reencode (struct commit*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* short_commit_name (struct commit*) ; 
 int /*<<< orphan*/  xmemdupz (char const*,int) ; 
 void* xstrfmt (char*,char const*,...) ; 

__attribute__((used)) static int get_message(struct commit *commit, struct commit_message *out)
{
	const char *abbrev, *subject;
	int subject_len;

	out->message = logmsg_reencode(commit, NULL, get_commit_output_encoding());
	abbrev = short_commit_name(commit);

	subject_len = find_commit_subject(out->message, &subject);

	out->subject = xmemdupz(subject, subject_len);
	out->label = xstrfmt("%s... %s", abbrev, out->subject);
	out->parent_label = xstrfmt("parent of %s", out->label);

	return 0;
}