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
 int /*<<< orphan*/  EXTATTR_NAMESPACE_USER ; 
 int /*<<< orphan*/  XATTR_NOFOLLOW ; 
 int extattr_set_link (char const*,int /*<<< orphan*/ ,char const*,void const*,size_t) ; 
 scalar_t__ lsetea (char const*,char const*,void const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ lsetxattr (char const*,char const*,void const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ setxattr (char const*,char const*,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
setXattr(const char *path, const char *name, const void *value, size_t size)
{
#if ARCHIVE_XATTR_SUPPORT
#if ARCHIVE_XATTR_LINUX
	if (lsetxattr(path, name, value, size, 0) == 0)
#elif ARCHIVE_XATTR_DARWIN
	if (setxattr(path, name, value, size, 0, XATTR_NOFOLLOW) == 0)
#elif ARCHIVE_XATTR_AIX
	if (lsetea(path, name, value, size, 0) == 0)
#elif ARCHIVE_XATTR_FREEBSD
	if (extattr_set_link(path, EXTATTR_NAMESPACE_USER, name + 5, value,
	    size) > -1)
#else
	if (0)
#endif
		return (1);
#else	/* !ARCHIVE_XATTR_SUPPORT */
	(void)path;     /* UNUSED */
	(void)name;	/* UNUSED */
	(void)value;	/* UNUSED */
	(void)size;	/* UNUSED */
#endif	/* !ARCHIVE_XATTR_SUPPORT */
	return (0);
}