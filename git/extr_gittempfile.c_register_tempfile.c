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
struct tempfile {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  activate_tempfile (struct tempfile*) ; 
 struct tempfile* new_tempfile () ; 
 int /*<<< orphan*/  strbuf_add_absolute_path (int /*<<< orphan*/ *,char const*) ; 

struct tempfile *register_tempfile(const char *path)
{
	struct tempfile *tempfile = new_tempfile();
	strbuf_add_absolute_path(&tempfile->filename, path);
	activate_tempfile(tempfile);
	return tempfile;
}