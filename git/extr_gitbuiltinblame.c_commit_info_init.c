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
struct commit_info {int /*<<< orphan*/  summary; int /*<<< orphan*/  committer_tz; int /*<<< orphan*/  committer_mail; int /*<<< orphan*/  committer; int /*<<< orphan*/  author_tz; int /*<<< orphan*/  author_mail; int /*<<< orphan*/  author; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void commit_info_init(struct commit_info *ci)
{

	strbuf_init(&ci->author, 0);
	strbuf_init(&ci->author_mail, 0);
	strbuf_init(&ci->author_tz, 0);
	strbuf_init(&ci->committer, 0);
	strbuf_init(&ci->committer_mail, 0);
	strbuf_init(&ci->committer_tz, 0);
	strbuf_init(&ci->summary, 0);
}