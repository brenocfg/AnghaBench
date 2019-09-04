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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  die_errno (char*,char const*) ; 
 int /*<<< orphan*/  hash_fd (int,char const*,char const*,unsigned int,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hash_object(const char *path, const char *type, const char *vpath,
			unsigned flags, int literally)
{
	int fd;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		die_errno("Cannot open '%s'", path);
	hash_fd(fd, type, vpath, flags, literally);
}