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
struct cache_entry {int ce_mode; } ;

/* Variables and functions */
 int S_IFMT ; 
 int S_IFREG ; 
 int /*<<< orphan*/  TEMPORARY_FILENAME_LENGTH ; 
 int create_file (char*,int) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int open_output_fd(char *path, const struct cache_entry *ce, int to_tempfile)
{
	int symlink = (ce->ce_mode & S_IFMT) != S_IFREG;
	if (to_tempfile) {
		xsnprintf(path, TEMPORARY_FILENAME_LENGTH, "%s",
			  symlink ? ".merge_link_XXXXXX" : ".merge_file_XXXXXX");
		return mkstemp(path);
	} else {
		return create_file(path, !symlink ? ce->ce_mode : 0666);
	}
}