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
struct strbuf {int len; int /*<<< orphan*/  buf; } ;
struct common_dir {char* path; scalar_t__ ignore_garbage; } ;
struct TYPE_2__ {int /*<<< orphan*/  different_commondir; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKDIR_FILE_GARBAGE ; 
 struct strbuf STRBUF_INIT ; 
 struct common_dir* common_list ; 
 scalar_t__ file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_git_dir () ; 
 int /*<<< orphan*/  report_garbage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 TYPE_1__* the_repository ; 

void report_linked_checkout_garbage(void)
{
	struct strbuf sb = STRBUF_INIT;
	const struct common_dir *p;
	int len;

	if (!the_repository->different_commondir)
		return;
	strbuf_addf(&sb, "%s/", get_git_dir());
	len = sb.len;
	for (p = common_list; p->path; p++) {
		const char *path = p->path;
		if (p->ignore_garbage)
			continue;
		strbuf_setlen(&sb, len);
		strbuf_addstr(&sb, path);
		if (file_exists(sb.buf))
			report_garbage(PACKDIR_FILE_GARBAGE, sb.buf);
	}
	strbuf_release(&sb);
}