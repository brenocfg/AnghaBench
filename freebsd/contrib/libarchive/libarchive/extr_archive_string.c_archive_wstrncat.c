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
typedef  scalar_t__ wchar_t ;
struct archive_wstring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __archive_errx (int,char*) ; 
 struct archive_wstring* archive_wstring_append (struct archive_wstring*,scalar_t__ const*,size_t) ; 

struct archive_wstring *
archive_wstrncat(struct archive_wstring *as, const wchar_t *p, size_t n)
{
	size_t s;
	const wchar_t *pp;

	/* Like strlen(p), except won't examine positions beyond p[n]. */
	s = 0;
	pp = p;
	while (s < n && *pp) {
		pp++;
		s++;
	}
	if ((as = archive_wstring_append(as, p, s)) == NULL)
		__archive_errx(1, "Out of memory");
	return (as);
}