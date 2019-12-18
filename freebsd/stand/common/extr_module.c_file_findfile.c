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
struct preloaded_file {int /*<<< orphan*/  f_type; int /*<<< orphan*/  f_name; struct preloaded_file* f_next; } ;

/* Variables and functions */
 struct preloaded_file* preloaded_files ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

struct preloaded_file *
file_findfile(const char *name, const char *type)
{
	struct preloaded_file *fp;

	for (fp = preloaded_files; fp != NULL; fp = fp->f_next) {
		if (((name == NULL) || !strcmp(name, fp->f_name)) &&
		  ((type == NULL) || !strcmp(type, fp->f_type)))
			break;
	}
	return (fp);
}