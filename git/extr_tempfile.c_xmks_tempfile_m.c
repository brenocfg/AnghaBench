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
struct tempfile {int dummy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die_errno (char*,int /*<<< orphan*/ ) ; 
 struct tempfile* mks_tempfile_m (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_add_absolute_path (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

struct tempfile *xmks_tempfile_m(const char *filename_template, int mode)
{
	struct tempfile *tempfile;
	struct strbuf full_template = STRBUF_INIT;

	strbuf_add_absolute_path(&full_template, filename_template);
	tempfile = mks_tempfile_m(full_template.buf, mode);
	if (!tempfile)
		die_errno("Unable to create temporary file '%s'",
			  full_template.buf);

	strbuf_release(&full_template);
	return tempfile;
}