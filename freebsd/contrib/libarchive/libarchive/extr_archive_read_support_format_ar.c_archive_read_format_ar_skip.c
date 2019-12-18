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
struct archive_read {TYPE_1__* format; } ;
struct ar {scalar_t__ entry_padding; scalar_t__ entry_bytes_unconsumed; scalar_t__ entry_bytes_remaining; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ __archive_read_consume (struct archive_read*,scalar_t__) ; 

__attribute__((used)) static int
archive_read_format_ar_skip(struct archive_read *a)
{
	int64_t bytes_skipped;
	struct ar* ar;

	ar = (struct ar *)(a->format->data);

	bytes_skipped = __archive_read_consume(a,
	    ar->entry_bytes_remaining + ar->entry_padding
	    + ar->entry_bytes_unconsumed);
	if (bytes_skipped < 0)
		return (ARCHIVE_FATAL);

	ar->entry_bytes_remaining = 0;
	ar->entry_bytes_unconsumed = 0;
	ar->entry_padding = 0;

	return (ARCHIVE_OK);
}