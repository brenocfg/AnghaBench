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
struct strbuf {char* buf; } ;
struct rename_cb {char* tmp_renamed_log; int /*<<< orphan*/  true_errno; } ;
struct files_ref_store {int dummy; } ;

/* Variables and functions */
 scalar_t__ EISDIR ; 
 struct strbuf STRBUF_INIT ; 
 char const* TMP_RENAMED_LOG ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 
 int /*<<< orphan*/  files_reflog_path (struct files_ref_store*,struct strbuf*,char const*) ; 
 int raceproof_create_file (char*,int /*<<< orphan*/ ,struct rename_cb*) ; 
 int /*<<< orphan*/  rename_tmp_log_callback ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rename_tmp_log(struct files_ref_store *refs, const char *newrefname)
{
	struct strbuf path = STRBUF_INIT;
	struct strbuf tmp = STRBUF_INIT;
	struct rename_cb cb;
	int ret;

	files_reflog_path(refs, &path, newrefname);
	files_reflog_path(refs, &tmp, TMP_RENAMED_LOG);
	cb.tmp_renamed_log = tmp.buf;
	ret = raceproof_create_file(path.buf, rename_tmp_log_callback, &cb);
	if (ret) {
		if (errno == EISDIR)
			error("directory not empty: %s", path.buf);
		else
			error("unable to move logfile %s to %s: %s",
			      tmp.buf, path.buf,
			      strerror(cb.true_errno));
	}

	strbuf_release(&path);
	strbuf_release(&tmp);
	return ret;
}