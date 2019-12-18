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
struct input_file {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct input_file* dopath (struct input_file*,char const*) ; 
 int /*<<< orphan*/  ensure_m4path () ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  set_input (struct input_file*,int /*<<< orphan*/ *,char const*) ; 

struct input_file *
fopen_trypath(struct input_file *i, const char *filename)
{
	FILE *f;

	f = fopen(filename, "r");
	if (f != NULL) {
		set_input(i, f, filename);
		return i;
	}
	if (filename[0] == '/')
		return NULL;

	ensure_m4path();

	return dopath(i, filename);
}