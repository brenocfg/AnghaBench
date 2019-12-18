#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct cfdata {scalar_t__ compressed_size; scalar_t__ uncompressed_bytes_remaining; scalar_t__ uncompressed_avail; scalar_t__ uncompressed_size; int /*<<< orphan*/  read_offset; scalar_t__ compressed_bytes_remaining; } ;
struct cab {TYPE_2__* entry_cffile; struct cfdata* entry_cfdata; int /*<<< orphan*/  cab_offset; } ;
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int folder; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 scalar_t__ ARCHIVE_FATAL ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,scalar_t__) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ cab_minimum_consume_cfdata (struct archive_read*,scalar_t__) ; 
 int cab_next_cfdata (struct archive_read*) ; 
 int /*<<< orphan*/  cab_read_ahead_cfdata (struct archive_read*,scalar_t__*) ; 
#define  iFoldCONTINUED_FROM_PREV 130 
#define  iFoldCONTINUED_PREV_AND_NEXT 129 
#define  iFoldCONTINUED_TO_NEXT 128 

__attribute__((used)) static int64_t
cab_consume_cfdata(struct archive_read *a, int64_t consumed_bytes)
{
	struct cab *cab = (struct cab *)(a->format->data);
	struct cfdata *cfdata;
	int64_t cbytes, rbytes;
	int err;

	rbytes = cab_minimum_consume_cfdata(a, consumed_bytes);
	if (rbytes < 0)
		return (ARCHIVE_FATAL);

	cfdata = cab->entry_cfdata;
	while (rbytes > 0) {
		ssize_t avail;

		if (cfdata->compressed_size == 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Invalid CFDATA");
			return (ARCHIVE_FATAL);
		}
		cbytes = cfdata->uncompressed_bytes_remaining;
		if (cbytes > rbytes)
			cbytes = rbytes;
		rbytes -= cbytes;

		if (cfdata->uncompressed_avail == 0 &&
		   (cab->entry_cffile->folder == iFoldCONTINUED_PREV_AND_NEXT ||
		    cab->entry_cffile->folder == iFoldCONTINUED_FROM_PREV)) {
			/* We have not read any data yet. */
			if (cbytes == cfdata->uncompressed_bytes_remaining) {
				/* Skip whole current CFDATA. */
				__archive_read_consume(a,
				    cfdata->compressed_size);
				cab->cab_offset += cfdata->compressed_size;
				cfdata->compressed_bytes_remaining = 0;
				cfdata->uncompressed_bytes_remaining = 0;
				err = cab_next_cfdata(a);
				if (err < 0)
					return (err);
				cfdata = cab->entry_cfdata;
				if (cfdata->uncompressed_size == 0) {
					switch (cab->entry_cffile->folder) {
					case iFoldCONTINUED_PREV_AND_NEXT:
					case iFoldCONTINUED_TO_NEXT:
					case iFoldCONTINUED_FROM_PREV:
						rbytes = 0;
						break;
					default:
						break;
					}
				}
				continue;
			}
			cfdata->read_offset += (uint16_t)cbytes;
			cfdata->uncompressed_bytes_remaining -= (uint16_t)cbytes;
			break;
		} else if (cbytes == 0) {
			err = cab_next_cfdata(a);
			if (err < 0)
				return (err);
			cfdata = cab->entry_cfdata;
			if (cfdata->uncompressed_size == 0) {
				switch (cab->entry_cffile->folder) {
				case iFoldCONTINUED_PREV_AND_NEXT:
				case iFoldCONTINUED_TO_NEXT:
				case iFoldCONTINUED_FROM_PREV:
					return (ARCHIVE_FATAL);
				default:
					break;
				}
			}
			continue;
		}
		while (cbytes > 0) {
			(void)cab_read_ahead_cfdata(a, &avail);
			if (avail <= 0)
				return (ARCHIVE_FATAL);
			if (avail > cbytes)
				avail = (ssize_t)cbytes;
			if (cab_minimum_consume_cfdata(a, avail) < 0)
				return (ARCHIVE_FATAL);
			cbytes -= avail;
		}
	}
	return (consumed_bytes);
}