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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct lock_file {TYPE_1__* tempfile; } ;
struct TYPE_2__ {int fd; } ;

/* Variables and functions */
 int LOCK_NO_DEREF ; 
 char const* LOCK_SUFFIX ; 
 struct strbuf STRBUF_INIT ; 
 TYPE_1__* create_tempfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_symlink (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int lock_file(struct lock_file *lk, const char *path, int flags)
{
	struct strbuf filename = STRBUF_INIT;

	strbuf_addstr(&filename, path);
	if (!(flags & LOCK_NO_DEREF))
		resolve_symlink(&filename);

	strbuf_addstr(&filename, LOCK_SUFFIX);
	lk->tempfile = create_tempfile(filename.buf);
	strbuf_release(&filename);
	return lk->tempfile ? lk->tempfile->fd : -1;
}