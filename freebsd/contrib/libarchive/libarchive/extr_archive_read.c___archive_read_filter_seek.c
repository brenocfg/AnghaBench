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
struct archive_read_filter {scalar_t__ end_of_file; scalar_t__ position; int /*<<< orphan*/  buffer; int /*<<< orphan*/  next; scalar_t__ client_avail; scalar_t__ avail; TYPE_1__* archive; int /*<<< orphan*/ * seek; scalar_t__ fatal; scalar_t__ closed; } ;
struct archive_read_client {unsigned int nodes; TYPE_2__* dataset; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {scalar_t__ begin_position; scalar_t__ total_size; } ;
struct TYPE_3__ {struct archive_read_client client; } ;

/* Variables and functions */
 scalar_t__ ARCHIVE_FAILED ; 
 scalar_t__ ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_OK ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  __LA_FALLTHROUGH ; 
 scalar_t__ client_seek_proxy (struct archive_read_filter*,scalar_t__,int const) ; 
 scalar_t__ client_switch_proxy (struct archive_read_filter*,unsigned int) ; 

int64_t
__archive_read_filter_seek(struct archive_read_filter *filter, int64_t offset,
    int whence)
{
	struct archive_read_client *client;
	int64_t r;
	unsigned int cursor;

	if (filter->closed || filter->fatal)
		return (ARCHIVE_FATAL);
	if (filter->seek == NULL)
		return (ARCHIVE_FAILED);

	client = &(filter->archive->client);
	switch (whence) {
	case SEEK_CUR:
		/* Adjust the offset and use SEEK_SET instead */
		offset += filter->position;
		__LA_FALLTHROUGH;
	case SEEK_SET:
		cursor = 0;
		while (1)
		{
			if (client->dataset[cursor].begin_position < 0 ||
			    client->dataset[cursor].total_size < 0 ||
			    client->dataset[cursor].begin_position +
			      client->dataset[cursor].total_size - 1 > offset ||
			    cursor + 1 >= client->nodes)
				break;
			r = client->dataset[cursor].begin_position +
				client->dataset[cursor].total_size;
			client->dataset[++cursor].begin_position = r;
		}
		while (1) {
			r = client_switch_proxy(filter, cursor);
			if (r != ARCHIVE_OK)
				return r;
			if ((r = client_seek_proxy(filter, 0, SEEK_END)) < 0)
				return r;
			client->dataset[cursor].total_size = r;
			if (client->dataset[cursor].begin_position +
			    client->dataset[cursor].total_size - 1 > offset ||
			    cursor + 1 >= client->nodes)
				break;
			r = client->dataset[cursor].begin_position +
				client->dataset[cursor].total_size;
			client->dataset[++cursor].begin_position = r;
		}
		offset -= client->dataset[cursor].begin_position;
		if (offset < 0
		    || offset > client->dataset[cursor].total_size)
			return ARCHIVE_FATAL;
		if ((r = client_seek_proxy(filter, offset, SEEK_SET)) < 0)
			return r;
		break;

	case SEEK_END:
		cursor = 0;
		while (1) {
			if (client->dataset[cursor].begin_position < 0 ||
			    client->dataset[cursor].total_size < 0 ||
			    cursor + 1 >= client->nodes)
				break;
			r = client->dataset[cursor].begin_position +
				client->dataset[cursor].total_size;
			client->dataset[++cursor].begin_position = r;
		}
		while (1) {
			r = client_switch_proxy(filter, cursor);
			if (r != ARCHIVE_OK)
				return r;
			if ((r = client_seek_proxy(filter, 0, SEEK_END)) < 0)
				return r;
			client->dataset[cursor].total_size = r;
			r = client->dataset[cursor].begin_position +
				client->dataset[cursor].total_size;
			if (cursor + 1 >= client->nodes)
				break;
			client->dataset[++cursor].begin_position = r;
		}
		while (1) {
			if (r + offset >=
			    client->dataset[cursor].begin_position)
				break;
			offset += client->dataset[cursor].total_size;
			if (cursor == 0)
				break;
			cursor--;
			r = client->dataset[cursor].begin_position +
				client->dataset[cursor].total_size;
		}
		offset = (r + offset) - client->dataset[cursor].begin_position;
		if ((r = client_switch_proxy(filter, cursor)) != ARCHIVE_OK)
			return r;
		r = client_seek_proxy(filter, offset, SEEK_SET);
		if (r < ARCHIVE_OK)
			return r;
		break;

	default:
		return (ARCHIVE_FATAL);
	}
	r += client->dataset[cursor].begin_position;

	if (r >= 0) {
		/*
		 * Ouch.  Clearing the buffer like this hurts, especially
		 * at bid time.  A lot of our efficiency at bid time comes
		 * from having bidders reuse the data we've already read.
		 *
		 * TODO: If the seek request is in data we already
		 * have, then don't call the seek callback.
		 *
		 * TODO: Zip seeks to end-of-file at bid time.  If
		 * other formats also start doing this, we may need to
		 * find a way for clients to fudge the seek offset to
		 * a block boundary.
		 *
		 * Hmmm... If whence was SEEK_END, we know the file
		 * size is (r - offset).  Can we use that to simplify
		 * the TODO items above?
		 */
		filter->avail = filter->client_avail = 0;
		filter->next = filter->buffer;
		filter->position = r;
		filter->end_of_file = 0;
	}
	return r;
}