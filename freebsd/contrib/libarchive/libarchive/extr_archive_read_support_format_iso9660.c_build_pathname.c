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
struct file_info {int /*<<< orphan*/  name; struct file_info* parent; } ;
struct archive_string {char const* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_strcat (struct archive_string*,char*) ; 
 int /*<<< orphan*/  archive_string_concat (struct archive_string*,int /*<<< orphan*/ *) ; 
 scalar_t__ archive_strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
build_pathname(struct archive_string *as, struct file_info *file, int depth)
{
	// Plain ISO9660 only allows 8 dir levels; if we get
	// to 1000, then something is very, very wrong.
	if (depth > 1000) {
		return NULL;
	}
	if (file->parent != NULL && archive_strlen(&file->parent->name) > 0) {
		if (build_pathname(as, file->parent, depth + 1) == NULL) {
			return NULL;
		}
		archive_strcat(as, "/");
	}
	if (archive_strlen(&file->name) == 0)
		archive_strcat(as, ".");
	else
		archive_string_concat(as, &file->name);
	return (as->s);
}