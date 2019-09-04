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
struct diff_filespec {int dummy; } ;

/* Variables and functions */
 struct diff_filespec* alloc_filespec (char const*) ; 
 char const* file_from_standard_input ; 
 int /*<<< orphan*/  fill_filespec (struct diff_filespec*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  populate_from_stdin (struct diff_filespec*) ; 

__attribute__((used)) static struct diff_filespec *noindex_filespec(const char *name, int mode)
{
	struct diff_filespec *s;

	if (!name)
		name = "/dev/null";
	s = alloc_filespec(name);
	fill_filespec(s, &null_oid, 0, mode);
	if (name == file_from_standard_input)
		populate_from_stdin(s);
	return s;
}