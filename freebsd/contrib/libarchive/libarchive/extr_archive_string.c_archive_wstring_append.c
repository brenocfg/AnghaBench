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
struct archive_wstring {size_t length; scalar_t__* s; } ;

/* Variables and functions */
 int /*<<< orphan*/ * archive_wstring_ensure (struct archive_wstring*,size_t) ; 
 int /*<<< orphan*/  wmemmove (scalar_t__*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static struct archive_wstring *
archive_wstring_append(struct archive_wstring *as, const wchar_t *p, size_t s)
{
	if (archive_wstring_ensure(as, as->length + s + 1) == NULL)
		return (NULL);
	if (s)
		wmemmove(as->s + as->length, p, s);
	as->length += s;
	as->s[as->length] = 0;
	return (as);
}