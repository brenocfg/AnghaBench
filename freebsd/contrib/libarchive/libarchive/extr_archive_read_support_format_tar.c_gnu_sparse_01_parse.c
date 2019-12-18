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
struct tar {int dummy; } ;
struct archive_read {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 scalar_t__ gnu_add_sparse_entry (struct archive_read*,struct tar*,scalar_t__,scalar_t__) ; 
 scalar_t__ tar_atol10 (char const*,int) ; 

__attribute__((used)) static int
gnu_sparse_01_parse(struct archive_read *a, struct tar *tar, const char *p)
{
	const char *e;
	int64_t offset = -1, size = -1;

	for (;;) {
		e = p;
		while (*e != '\0' && *e != ',') {
			if (*e < '0' || *e > '9')
				return (ARCHIVE_WARN);
			e++;
		}
		if (offset < 0) {
			offset = tar_atol10(p, e - p);
			if (offset < 0)
				return (ARCHIVE_WARN);
		} else {
			size = tar_atol10(p, e - p);
			if (size < 0)
				return (ARCHIVE_WARN);
			if (gnu_add_sparse_entry(a, tar, offset, size)
			    != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			offset = -1;
		}
		if (*e == '\0')
			return (ARCHIVE_OK);
		p = e + 1;
	}
}