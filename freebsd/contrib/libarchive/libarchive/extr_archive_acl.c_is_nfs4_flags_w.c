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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int ARCHIVE_ENTRY_ACL_ENTRY_DIRECTORY_INHERIT ; 
 int ARCHIVE_ENTRY_ACL_ENTRY_FAILED_ACCESS ; 
 int ARCHIVE_ENTRY_ACL_ENTRY_FILE_INHERIT ; 
 int ARCHIVE_ENTRY_ACL_ENTRY_INHERITED ; 
 int ARCHIVE_ENTRY_ACL_ENTRY_INHERIT_ONLY ; 
 int ARCHIVE_ENTRY_ACL_ENTRY_NO_PROPAGATE_INHERIT ; 
 int ARCHIVE_ENTRY_ACL_ENTRY_SUCCESSFUL_ACCESS ; 

__attribute__((used)) static int
is_nfs4_flags_w(const wchar_t *start, const wchar_t *end, int *permset)
{
	const wchar_t *p = start;

	while (p < end) {
		switch(*p++) {
		case L'f':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_FILE_INHERIT;
			break;
		case L'd':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_DIRECTORY_INHERIT;
			break;
		case L'i':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_INHERIT_ONLY;
			break;
		case L'n':
			*permset |=
			    ARCHIVE_ENTRY_ACL_ENTRY_NO_PROPAGATE_INHERIT;
			break;
		case L'S':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_SUCCESSFUL_ACCESS;
			break;
		case L'F':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_FAILED_ACCESS;
			break;
		case L'I':
			*permset |= ARCHIVE_ENTRY_ACL_ENTRY_INHERITED;
			break;
		case L'-':
			break;
		default:
			return (0);
		}
	}
	return (1);
}