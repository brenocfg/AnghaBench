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
struct archive_string {int /*<<< orphan*/  length; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  __archive_errx (int,char*) ; 
 int /*<<< orphan*/ * archive_string_append (struct archive_string*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
archive_string_concat(struct archive_string *dest, struct archive_string *src)
{
	if (archive_string_append(dest, src->s, src->length) == NULL)
		__archive_errx(1, "Out of memory");
}