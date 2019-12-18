#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* name; } ;
struct TYPE_7__ {char* s; size_t length; } ;
struct tree {size_t dirname_length; char* basename; TYPE_1__ restore_time; TYPE_2__ path; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_strappend_char (TYPE_2__*,char) ; 
 int /*<<< orphan*/  archive_string_ensure (TYPE_2__*,size_t) ; 
 int archive_strlen (TYPE_2__*) ; 
 int /*<<< orphan*/  archive_strncat (TYPE_2__*,char const*,size_t) ; 

__attribute__((used)) static void
tree_append(struct tree *t, const char *name, size_t name_length)
{
	size_t size_needed;

	t->path.s[t->dirname_length] = '\0';
	t->path.length = t->dirname_length;
	/* Strip trailing '/' from name, unless entire name is "/". */
	while (name_length > 1 && name[name_length - 1] == '/')
		name_length--;

	/* Resize pathname buffer as needed. */
	size_needed = name_length + t->dirname_length + 2;
	archive_string_ensure(&t->path, size_needed);
	/* Add a separating '/' if it's needed. */
	if (t->dirname_length > 0 && t->path.s[archive_strlen(&t->path)-1] != '/')
		archive_strappend_char(&t->path, '/');
	t->basename = t->path.s + archive_strlen(&t->path);
	archive_strncat(&t->path, name, name_length);
	t->restore_time.name = t->basename;
}