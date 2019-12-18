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
struct strbuf {char* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  append_basename (struct strbuf*,char const*,char const*) ; 
 char const* file_from_standard_input ; 
 unsigned int is_directory (char const*) ; 

__attribute__((used)) static void fixup_paths(const char **path, struct strbuf *replacement)
{
	unsigned int isdir0, isdir1;

	if (path[0] == file_from_standard_input ||
	    path[1] == file_from_standard_input)
		return;
	isdir0 = is_directory(path[0]);
	isdir1 = is_directory(path[1]);
	if (isdir0 == isdir1)
		return;
	if (isdir0) {
		append_basename(replacement, path[0], path[1]);
		path[0] = replacement->buf;
	} else {
		append_basename(replacement, path[1], path[0]);
		path[1] = replacement->buf;
	}
}