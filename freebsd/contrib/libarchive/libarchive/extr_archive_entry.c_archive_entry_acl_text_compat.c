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
 int ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID ; 
 int ARCHIVE_ENTRY_ACL_STYLE_MARK_DEFAULT ; 
 int ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA ; 
 int ARCHIVE_ENTRY_ACL_TYPE_POSIX1E ; 
 int OLD_ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID ; 
 int OLD_ARCHIVE_ENTRY_ACL_STYLE_MARK_DEFAULT ; 

__attribute__((used)) static int
archive_entry_acl_text_compat(int *flags)
{
	if ((*flags & ARCHIVE_ENTRY_ACL_TYPE_POSIX1E) == 0)
		return (1);

	/* ABI compat with old ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID */
	if ((*flags & OLD_ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID) != 0)
		*flags |= ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID;

	/* ABI compat with old ARCHIVE_ENTRY_ACL_STYLE_MARK_DEFAULT */
	if ((*flags & OLD_ARCHIVE_ENTRY_ACL_STYLE_MARK_DEFAULT) != 0)
		*flags |=  ARCHIVE_ENTRY_ACL_STYLE_MARK_DEFAULT;

	*flags |= ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA;

	return (0);
}