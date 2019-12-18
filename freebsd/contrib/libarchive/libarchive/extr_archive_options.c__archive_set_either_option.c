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
struct archive {int dummy; } ;
typedef  int (* option_handler ) (struct archive*,char const*,char const*,char const*) ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 

int
_archive_set_either_option(struct archive *a, const char *m, const char *o, const char *v,
    option_handler use_format_option, option_handler use_filter_option)
{
	int r1, r2;

	if (o == NULL && v == NULL)
		return (ARCHIVE_OK);
	if (o == NULL)
		return (ARCHIVE_FAILED);

	r1 = use_format_option(a, m, o, v);
	if (r1 == ARCHIVE_FATAL)
		return (ARCHIVE_FATAL);

	r2 = use_filter_option(a, m, o, v);
	if (r2 == ARCHIVE_FATAL)
		return (ARCHIVE_FATAL);

	if (r2 == ARCHIVE_WARN - 1)
		return r1;
	return r1 > r2 ? r1 : r2;
}