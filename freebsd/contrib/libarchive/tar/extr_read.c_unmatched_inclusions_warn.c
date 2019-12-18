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

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int archive_match_path_unmatched_inclusions (struct archive*) ; 
 int archive_match_path_unmatched_inclusions_next (struct archive*,char const**) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*,char const*,char const*) ; 

__attribute__((used)) static int
unmatched_inclusions_warn(struct archive *matching, const char *msg)
{
	const char *p;
	int r;

	if (matching == NULL)
		return (0);

	while ((r = archive_match_path_unmatched_inclusions_next(
	    matching, &p)) == ARCHIVE_OK)
		lafe_warnc(0, "%s: %s", p, msg);
	if (r == ARCHIVE_FATAL)
		lafe_errc(1, errno, "Out of memory");

	return (archive_match_path_unmatched_inclusions(matching));
}