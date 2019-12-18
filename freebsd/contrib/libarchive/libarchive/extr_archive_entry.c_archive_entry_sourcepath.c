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
struct archive_entry {int /*<<< orphan*/  ae_sourcepath; int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  __archive_errx (int,char*) ; 
 scalar_t__ archive_mstring_get_mbs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ errno ; 

const char *
archive_entry_sourcepath(struct archive_entry *entry)
{
	const char *p;
	if (archive_mstring_get_mbs(
	    entry->archive, &entry->ae_sourcepath, &p) == 0)
		return (p);
	if (errno == ENOMEM)
		__archive_errx(1, "No memory");
	return (NULL);
}