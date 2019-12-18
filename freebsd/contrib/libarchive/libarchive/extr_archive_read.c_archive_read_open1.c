#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct archive_read_filter {char* name; struct archive_read_filter* upstream; int /*<<< orphan*/  code; int /*<<< orphan*/  (* sswitch ) (struct archive_read_filter*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  close; int /*<<< orphan*/  seek; int /*<<< orphan*/  skip; int /*<<< orphan*/  read; int /*<<< orphan*/  open; int /*<<< orphan*/  data; struct archive_read* archive; int /*<<< orphan*/ * bidder; } ;
struct TYPE_9__ {void* state; } ;
struct TYPE_8__ {int (* opener ) (TYPE_3__*,int /*<<< orphan*/ ) ;unsigned int nodes; TYPE_1__* dataset; int /*<<< orphan*/  (* closer ) (TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * reader; } ;
struct archive_read {struct archive_read_filter* filter; TYPE_3__ archive; int /*<<< orphan*/ * formats; int /*<<< orphan*/ * format; int /*<<< orphan*/  bypass_filter_bidding; TYPE_2__ client; } ;
struct archive {int dummy; } ;
struct TYPE_7__ {scalar_t__ begin_position; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FILTER_NONE ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 void* ARCHIVE_STATE_FATAL ; 
 void* ARCHIVE_STATE_HEADER ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_clear_error (TYPE_3__*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 struct archive_read_filter* calloc (int,int) ; 
 int choose_filters (struct archive_read*) ; 
 int choose_format (struct archive_read*) ; 
 int /*<<< orphan*/  client_close_proxy ; 
 int /*<<< orphan*/  client_open_proxy ; 
 int /*<<< orphan*/  client_read_proxy ; 
 int /*<<< orphan*/  client_seek_proxy ; 
 int /*<<< orphan*/  client_skip_proxy ; 
 int /*<<< orphan*/  client_switch_proxy (struct archive_read_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_filters (struct archive_read*) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ) ; 

int
archive_read_open1(struct archive *_a)
{
	struct archive_read *a = (struct archive_read *)_a;
	struct archive_read_filter *filter, *tmp;
	int slot, e = ARCHIVE_OK;
	unsigned int i;

	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,
	    "archive_read_open");
	archive_clear_error(&a->archive);

	if (a->client.reader == NULL) {
		archive_set_error(&a->archive, EINVAL,
		    "No reader function provided to archive_read_open");
		a->archive.state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}

	/* Open data source. */
	if (a->client.opener != NULL) {
		e = (a->client.opener)(&a->archive, a->client.dataset[0].data);
		if (e != 0) {
			/* If the open failed, call the closer to clean up. */
			if (a->client.closer) {
				for (i = 0; i < a->client.nodes; i++)
					(a->client.closer)(&a->archive,
					    a->client.dataset[i].data);
			}
			return (e);
		}
	}

	filter = calloc(1, sizeof(*filter));
	if (filter == NULL)
		return (ARCHIVE_FATAL);
	filter->bidder = NULL;
	filter->upstream = NULL;
	filter->archive = a;
	filter->data = a->client.dataset[0].data;
	filter->open = client_open_proxy;
	filter->read = client_read_proxy;
	filter->skip = client_skip_proxy;
	filter->seek = client_seek_proxy;
	filter->close = client_close_proxy;
	filter->sswitch = client_switch_proxy;
	filter->name = "none";
	filter->code = ARCHIVE_FILTER_NONE;

	a->client.dataset[0].begin_position = 0;
	if (!a->filter || !a->bypass_filter_bidding)
	{
		a->filter = filter;
		/* Build out the input pipeline. */
		e = choose_filters(a);
		if (e < ARCHIVE_WARN) {
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		}
	}
	else
	{
		/* Need to add "NONE" type filter at the end of the filter chain */
		tmp = a->filter;
		while (tmp->upstream)
			tmp = tmp->upstream;
		tmp->upstream = filter;
	}

	if (!a->format)
	{
		slot = choose_format(a);
		if (slot < 0) {
			close_filters(a);
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		}
		a->format = &(a->formats[slot]);
	}

	a->archive.state = ARCHIVE_STATE_HEADER;

	/* Ensure libarchive starts from the first node in a multivolume set */
	client_switch_proxy(a->filter, 0);
	return (e);
}