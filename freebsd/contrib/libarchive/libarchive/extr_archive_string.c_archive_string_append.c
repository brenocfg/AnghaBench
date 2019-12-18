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
struct archive_string {size_t length; scalar_t__* s; } ;

/* Variables and functions */
 int /*<<< orphan*/ * archive_string_ensure (struct archive_string*,size_t) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,char const*,size_t) ; 

__attribute__((used)) static struct archive_string *
archive_string_append(struct archive_string *as, const char *p, size_t s)
{
	if (archive_string_ensure(as, as->length + s + 1) == NULL)
		return (NULL);
	if (s)
		memmove(as->s + as->length, p, s);
	as->length += s;
	as->s[as->length] = 0;
	return (as);
}