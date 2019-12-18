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
struct archive_write {int (* format_options ) (struct archive_write*,char const*,char const*) ;int /*<<< orphan*/ * format_name; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 
 int ARCHIVE_WARN ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 int stub1 (struct archive_write*,char const*,char const*) ; 

__attribute__((used)) static int
archive_set_format_option(struct archive *_a, const char *m, const char *o,
    const char *v)
{
	struct archive_write *a = (struct archive_write *)_a;

	if (a->format_name == NULL)
		return (m == NULL)?ARCHIVE_FAILED:ARCHIVE_WARN - 1;
	/* If the format name didn't match, return a special code for
	 * _archive_set_option[s]. */
	if (m != NULL && strcmp(m, a->format_name) != 0)
		return (ARCHIVE_WARN - 1);
	if (a->format_options == NULL)
		return (ARCHIVE_WARN);
	return a->format_options(a, o, v);
}