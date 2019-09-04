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

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 char* get_mtime_path (char const*) ; 
 int open (char const*,int,int) ; 

__attribute__((used)) static int create_file(const char *path)
{
	int fd;
	path = get_mtime_path(path);
	fd = open(path, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		die_errno(_("failed to create file %s"), path);
	return fd;
}