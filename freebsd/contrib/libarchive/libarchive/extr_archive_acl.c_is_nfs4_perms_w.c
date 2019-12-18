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
 int ARCHIVE_ENTRY_ACL_APPEND_DATA ; 
 int ARCHIVE_ENTRY_ACL_DELETE ; 
 int ARCHIVE_ENTRY_ACL_DELETE_CHILD ; 
 int ARCHIVE_ENTRY_ACL_EXECUTE ; 
 int ARCHIVE_ENTRY_ACL_READ_ACL ; 
 int ARCHIVE_ENTRY_ACL_READ_ATTRIBUTES ; 
 int ARCHIVE_ENTRY_ACL_READ_DATA ; 
 int ARCHIVE_ENTRY_ACL_READ_NAMED_ATTRS ; 
 int ARCHIVE_ENTRY_ACL_SYNCHRONIZE ; 
 int ARCHIVE_ENTRY_ACL_WRITE_ACL ; 
 int ARCHIVE_ENTRY_ACL_WRITE_ATTRIBUTES ; 
 int ARCHIVE_ENTRY_ACL_WRITE_DATA ; 
 int ARCHIVE_ENTRY_ACL_WRITE_NAMED_ATTRS ; 
 int ARCHIVE_ENTRY_ACL_WRITE_OWNER ; 

__attribute__((used)) static int
is_nfs4_perms_w(const wchar_t *start, const wchar_t *end, int *permset)
{
	const wchar_t *p = start;

	while (p < end) {
		switch (*p++) {
		case L'r':
			*permset |= ARCHIVE_ENTRY_ACL_READ_DATA;
			break;
		case L'w':
			*permset |= ARCHIVE_ENTRY_ACL_WRITE_DATA;
			break;
		case L'x':
			*permset |= ARCHIVE_ENTRY_ACL_EXECUTE;
			break;
		case L'p':
			*permset |= ARCHIVE_ENTRY_ACL_APPEND_DATA;
			break;
		case L'D':
			*permset |= ARCHIVE_ENTRY_ACL_DELETE_CHILD;
			break;
		case L'd':
			*permset |= ARCHIVE_ENTRY_ACL_DELETE;
			break;
		case L'a':
			*permset |= ARCHIVE_ENTRY_ACL_READ_ATTRIBUTES;
			break;
		case L'A':
			*permset |= ARCHIVE_ENTRY_ACL_WRITE_ATTRIBUTES;
			break;
		case L'R':
			*permset |= ARCHIVE_ENTRY_ACL_READ_NAMED_ATTRS;
			break;
		case L'W':
			*permset |= ARCHIVE_ENTRY_ACL_WRITE_NAMED_ATTRS;
			break;
		case L'c':
			*permset |= ARCHIVE_ENTRY_ACL_READ_ACL;
			break;
		case L'C':
			*permset |= ARCHIVE_ENTRY_ACL_WRITE_ACL;
			break;
		case L'o':
			*permset |= ARCHIVE_ENTRY_ACL_WRITE_OWNER;
			break;
		case L's':
			*permset |= ARCHIVE_ENTRY_ACL_SYNCHRONIZE;
			break;
		case L'-':
			break;
		default:
			return(0);
		}
	}
	return (1);
}