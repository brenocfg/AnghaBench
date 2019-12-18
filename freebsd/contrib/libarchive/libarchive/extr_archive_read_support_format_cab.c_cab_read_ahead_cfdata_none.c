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
struct cfdata {scalar_t__ uncompressed_bytes_remaining; void const* sum_ptr; scalar_t__ unconsumed; int /*<<< orphan*/  uncompressed_size; int /*<<< orphan*/  uncompressed_avail; } ;
struct cab {struct cfdata* entry_cfdata; } ;
struct archive_read {TYPE_1__* format; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 void* __archive_read_ahead (struct archive_read*,int,scalar_t__*) ; 
 scalar_t__ truncated_error (struct archive_read*) ; 

__attribute__((used)) static const void *
cab_read_ahead_cfdata_none(struct archive_read *a, ssize_t *avail)
{
	struct cab *cab = (struct cab *)(a->format->data);
	struct cfdata *cfdata;
	const void *d;

	cfdata = cab->entry_cfdata;

	/*
	 * Note: '1' here is a performance optimization.
	 * Recall that the decompression layer returns a count of
	 * available bytes; asking for more than that forces the
	 * decompressor to combine reads by copying data.
	 */
	d = __archive_read_ahead(a, 1, avail);
	if (*avail <= 0) {
		*avail = truncated_error(a);
		return (NULL);
	}
	if (*avail > cfdata->uncompressed_bytes_remaining)
		*avail = cfdata->uncompressed_bytes_remaining;
	cfdata->uncompressed_avail = cfdata->uncompressed_size;
	cfdata->unconsumed = *avail;
	cfdata->sum_ptr = d;
	return (d);
}