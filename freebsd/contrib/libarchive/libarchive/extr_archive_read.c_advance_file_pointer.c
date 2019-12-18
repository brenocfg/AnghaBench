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
struct archive_read_filter {int fatal; scalar_t__ avail; size_t next; size_t position; size_t client_avail; char const* client_next; int (* skip ) (struct archive_read_filter*,int) ;scalar_t__ (* read ) (struct archive_read_filter*,int /*<<< orphan*/ **) ;int end_of_file; scalar_t__ client_total; int /*<<< orphan*/ * client_buff; TYPE_2__* archive; } ;
typedef  scalar_t__ ssize_t ;
typedef  int int64_t ;
struct TYPE_3__ {int cursor; int nodes; } ;
struct TYPE_4__ {TYPE_1__ client; } ;

/* Variables and functions */
 scalar_t__ ARCHIVE_OK ; 
 scalar_t__ client_switch_proxy (struct archive_read_filter*,int) ; 
 scalar_t__ minimum (int,int) ; 
 int stub1 (struct archive_read_filter*,int) ; 
 scalar_t__ stub2 (struct archive_read_filter*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int64_t
advance_file_pointer(struct archive_read_filter *filter, int64_t request)
{
	int64_t bytes_skipped, total_bytes_skipped = 0;
	ssize_t bytes_read;
	size_t min;

	if (filter->fatal)
		return (-1);

	/* Use up the copy buffer first. */
	if (filter->avail > 0) {
		min = (size_t)minimum(request, (int64_t)filter->avail);
		filter->next += min;
		filter->avail -= min;
		request -= min;
		filter->position += min;
		total_bytes_skipped += min;
	}

	/* Then use up the client buffer. */
	if (filter->client_avail > 0) {
		min = (size_t)minimum(request, (int64_t)filter->client_avail);
		filter->client_next += min;
		filter->client_avail -= min;
		request -= min;
		filter->position += min;
		total_bytes_skipped += min;
	}
	if (request == 0)
		return (total_bytes_skipped);

	/* If there's an optimized skip function, use it. */
	if (filter->skip != NULL) {
		bytes_skipped = (filter->skip)(filter, request);
		if (bytes_skipped < 0) {	/* error */
			filter->fatal = 1;
			return (bytes_skipped);
		}
		filter->position += bytes_skipped;
		total_bytes_skipped += bytes_skipped;
		request -= bytes_skipped;
		if (request == 0)
			return (total_bytes_skipped);
	}

	/* Use ordinary reads as necessary to complete the request. */
	for (;;) {
		bytes_read = (filter->read)(filter, &filter->client_buff);
		if (bytes_read < 0) {
			filter->client_buff = NULL;
			filter->fatal = 1;
			return (bytes_read);
		}

		if (bytes_read == 0) {
			if (filter->archive->client.cursor !=
			      filter->archive->client.nodes - 1) {
				if (client_switch_proxy(filter,
				    filter->archive->client.cursor + 1)
				    == ARCHIVE_OK)
					continue;
			}
			filter->client_buff = NULL;
			filter->end_of_file = 1;
			return (total_bytes_skipped);
		}

		if (bytes_read >= request) {
			filter->client_next =
			    ((const char *)filter->client_buff) + request;
			filter->client_avail = (size_t)(bytes_read - request);
			filter->client_total = bytes_read;
			total_bytes_skipped += request;
			filter->position += request;
			return (total_bytes_skipped);
		}

		filter->position += bytes_read;
		total_bytes_skipped += bytes_read;
		request -= bytes_read;
	}
}