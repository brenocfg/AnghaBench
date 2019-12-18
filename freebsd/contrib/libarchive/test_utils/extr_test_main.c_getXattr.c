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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTATTR_NAMESPACE_USER ; 
 int /*<<< orphan*/  XATTR_NOFOLLOW ; 
 scalar_t__ extattr_get_link (char const*,int /*<<< orphan*/ ,char const*,void*,scalar_t__) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ getxattr (char const*,char const*,void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lgetea (char const*,char const*,void*,scalar_t__) ; 
 scalar_t__ lgetxattr (char const*,char const*,void*,scalar_t__) ; 
 void* malloc (scalar_t__) ; 

void *
getXattr(const char *path, const char *name, size_t *sizep)
{ 
	void *value = NULL;
#if ARCHIVE_XATTR_SUPPORT
	ssize_t size;
#if ARCHIVE_XATTR_LINUX
	size = lgetxattr(path, name, NULL, 0);
#elif ARCHIVE_XATTR_DARWIN
	size = getxattr(path, name, NULL, 0, 0, XATTR_NOFOLLOW);
#elif ARCHIVE_XATTR_AIX
	size = lgetea(path, name, NULL, 0);
#elif ARCHIVE_XATTR_FREEBSD
	size = extattr_get_link(path, EXTATTR_NAMESPACE_USER, name + 5,
	    NULL, 0);
#endif

	if (size >= 0) {
		value = malloc(size);
#if ARCHIVE_XATTR_LINUX
		size = lgetxattr(path, name, value, size);
#elif ARCHIVE_XATTR_DARWIN
		size = getxattr(path, name, value, size, 0, XATTR_NOFOLLOW);
#elif ARCHIVE_XATTR_AIX
		size = lgetea(path, name, value, size);
#elif ARCHIVE_XATTR_FREEBSD
		size = extattr_get_link(path, EXTATTR_NAMESPACE_USER, name + 5,
		    value, size);
#endif
		if (size < 0) {
			free(value);
			value = NULL;
		}
	}
	if (size < 0)
		*sizep = 0;
	else
		*sizep = (size_t)size;
#else	/* !ARCHIVE_XATTR_SUPPORT */
	(void)path;	/* UNUSED */
	(void)name;	/* UNUSED */
	*sizep = 0;
#endif 	/* !ARCHIVE_XATTR_SUPPORT */
	return (value);
}