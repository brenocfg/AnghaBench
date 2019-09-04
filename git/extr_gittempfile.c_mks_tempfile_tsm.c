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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct tempfile {scalar_t__ fd; TYPE_1__ filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  activate_tempfile (struct tempfile*) ; 
 int /*<<< orphan*/  deactivate_tempfile (struct tempfile*) ; 
 char* getenv (char*) ; 
 scalar_t__ git_mkstemps_mode (int /*<<< orphan*/ ,int,int) ; 
 struct tempfile* new_tempfile () ; 
 int /*<<< orphan*/  strbuf_addf (TYPE_1__*,char*,char const*,char const*) ; 

struct tempfile *mks_tempfile_tsm(const char *filename_template, int suffixlen, int mode)
{
	struct tempfile *tempfile = new_tempfile();
	const char *tmpdir;

	tmpdir = getenv("TMPDIR");
	if (!tmpdir)
		tmpdir = "/tmp";

	strbuf_addf(&tempfile->filename, "%s/%s", tmpdir, filename_template);
	tempfile->fd = git_mkstemps_mode(tempfile->filename.buf, suffixlen, mode);
	if (tempfile->fd < 0) {
		deactivate_tempfile(tempfile);
		return NULL;
	}
	activate_tempfile(tempfile);
	return tempfile;
}