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
struct archive_acl {int dummy; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  __LA_MODE_T ;

/* Variables and functions */
 int ARCHIVE_OK ; 

int
archive_write_disk_set_acls(struct archive *a, int fd, const char *name,
    struct archive_acl *abstract_acl, __LA_MODE_T mode)
{
	(void)a; /* UNUSED */
	(void)fd; /* UNUSED */
	(void)name; /* UNUSED */
	(void)abstract_acl; /* UNUSED */
	(void)mode; /* UNUSED */
	return (ARCHIVE_OK);
}