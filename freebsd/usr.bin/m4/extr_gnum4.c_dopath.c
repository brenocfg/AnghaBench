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
struct path_entry {char* name; struct path_entry* next; } ;
struct input_file {int dummy; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 struct path_entry* first ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  set_input (struct input_file*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 

__attribute__((used)) static
struct input_file *
dopath(struct input_file *i, const char *filename)
{
	char path[PATH_MAX];
	struct path_entry *pe;
	FILE *f;

	for (pe = first; pe; pe = pe->next) {
		snprintf(path, sizeof(path), "%s/%s", pe->name, filename);
		if ((f = fopen(path, "r")) != NULL) {
			set_input(i, f, path);
			return i;
		}
	}
	return NULL;
}