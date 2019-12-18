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
struct archive_write {int /*<<< orphan*/  archive; scalar_t__ format_data; } ;
struct ar_w {size_t entry_bytes_remaining; scalar_t__ is_strtab; int has_strtab; char* strtab; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int __archive_write_output (struct archive_write*,void const*,size_t) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 

__attribute__((used)) static ssize_t
archive_write_ar_data(struct archive_write *a, const void *buff, size_t s)
{
	struct ar_w *ar;
	int ret;

	ar = (struct ar_w *)a->format_data;
	if (s > ar->entry_bytes_remaining)
		s = (size_t)ar->entry_bytes_remaining;

	if (ar->is_strtab > 0) {
		if (ar->has_strtab > 0) {
			archive_set_error(&a->archive, EINVAL,
			    "More than one string tables exist");
			return (ARCHIVE_WARN);
		}

		ar->strtab = (char *)malloc(s + 1);
		if (ar->strtab == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate strtab buffer");
			return (ARCHIVE_FATAL);
		}
		memcpy(ar->strtab, buff, s);
		ar->strtab[s] = '\0';
		ar->has_strtab = 1;
	}

	ret = __archive_write_output(a, buff, s);
	if (ret != ARCHIVE_OK)
		return (ret);

	ar->entry_bytes_remaining -= s;
	return (s);
}