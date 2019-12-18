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
struct archive_write_disk {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int create_dir (struct archive_write_disk*,char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
create_parent_dir(struct archive_write_disk *a, char *path)
{
	char *slash;
	int r;

	/* Remove tail element to obtain parent name. */
	slash = strrchr(path, '/');
	if (slash == NULL)
		return (ARCHIVE_OK);
	*slash = '\0';
	r = create_dir(a, path);
	*slash = '/';
	return (r);
}