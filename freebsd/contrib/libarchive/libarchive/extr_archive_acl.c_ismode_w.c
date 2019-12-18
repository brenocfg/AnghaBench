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
 int ARCHIVE_ENTRY_ACL_EXECUTE ; 
 int ARCHIVE_ENTRY_ACL_READ ; 
 int ARCHIVE_ENTRY_ACL_WRITE ; 

__attribute__((used)) static int
ismode_w(const wchar_t *start, const wchar_t *end, int *permset)
{
	const wchar_t *p;

	if (start >= end)
		return (0);
	p = start;
	*permset = 0;
	while (p < end) {
		switch (*p++) {
		case L'r': case L'R':
			*permset |= ARCHIVE_ENTRY_ACL_READ;
			break;
		case L'w': case L'W':
			*permset |= ARCHIVE_ENTRY_ACL_WRITE;
			break;
		case L'x': case L'X':
			*permset |= ARCHIVE_ENTRY_ACL_EXECUTE;
			break;
		case L'-':
			break;
		default:
			return (0);
		}
	}
	return (1);
}