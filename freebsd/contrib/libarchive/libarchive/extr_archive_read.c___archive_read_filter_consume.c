#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct archive_read_filter {TYPE_1__* archive; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 scalar_t__ ARCHIVE_FATAL ; 
 scalar_t__ advance_file_pointer (struct archive_read_filter*,scalar_t__) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int64_t
__archive_read_filter_consume(struct archive_read_filter * filter,
    int64_t request)
{
	int64_t skipped;

	if (request < 0)
		return ARCHIVE_FATAL;
	if (request == 0)
		return 0;

	skipped = advance_file_pointer(filter, request);
	if (skipped == request)
		return (skipped);
	/* We hit EOF before we satisfied the skip request. */
	if (skipped < 0)  /* Map error code to 0 for error message below. */
		skipped = 0;
	archive_set_error(&filter->archive->archive,
	    ARCHIVE_ERRNO_MISC,
	    "Truncated input file (needed %jd bytes, only %jd available)",
	    (intmax_t)request, (intmax_t)skipped);
	return (ARCHIVE_FATAL);
}