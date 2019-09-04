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
struct TYPE_2__ {char* prefix; } ;

/* Variables and functions */
 int DO_NONFLAGS ; 
 int DO_NOREV ; 
 int filter ; 
 int /*<<< orphan*/  free (char*) ; 
 char* prefix_filename (char const*,char const*) ; 
 int /*<<< orphan*/  show (char const*) ; 
 int /*<<< orphan*/  show_default () ; 
 TYPE_1__* startup_info ; 

__attribute__((used)) static int show_file(const char *arg, int output_prefix)
{
	show_default();
	if ((filter & (DO_NONFLAGS|DO_NOREV)) == (DO_NONFLAGS|DO_NOREV)) {
		if (output_prefix) {
			const char *prefix = startup_info->prefix;
			char *fname = prefix_filename(prefix, arg);
			show(fname);
			free(fname);
		} else
			show(arg);
		return 1;
	}
	return 0;
}