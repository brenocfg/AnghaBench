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
struct strbuf {scalar_t__ len; scalar_t__ buf; } ;
struct lock_file {int /*<<< orphan*/  tempfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  LOCK_SUFFIX ; 
 scalar_t__ LOCK_SUFFIX_LEN ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  get_tempfile_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,scalar_t__) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 

char *get_locked_file_path(struct lock_file *lk)
{
	struct strbuf ret = STRBUF_INIT;

	strbuf_addstr(&ret, get_tempfile_path(lk->tempfile));
	if (ret.len <= LOCK_SUFFIX_LEN ||
	    strcmp(ret.buf + ret.len - LOCK_SUFFIX_LEN, LOCK_SUFFIX))
		BUG("get_locked_file_path() called for malformed lock object");
	/* remove ".lock": */
	strbuf_setlen(&ret, ret.len - LOCK_SUFFIX_LEN);
	return strbuf_detach(&ret, NULL);
}