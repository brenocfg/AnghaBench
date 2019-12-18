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
struct archive_read_data_node {int begin_position; int total_size; void* data; } ;
struct TYPE_2__ {int nodes; struct archive_read_data_node* dataset; } ;
struct archive_read {TYPE_1__ client; int /*<<< orphan*/  archive; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ calloc (int,int) ; 

int
archive_read_set_callback_data2(struct archive *_a, void *client_data,
    unsigned int iindex)
{
	struct archive_read *a = (struct archive_read *)_a;
	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,
	    "archive_read_set_callback_data2");

	if (a->client.nodes == 0)
	{
		a->client.dataset = (struct archive_read_data_node *)
		    calloc(1, sizeof(*a->client.dataset));
		if (a->client.dataset == NULL)
		{
			archive_set_error(&a->archive, ENOMEM,
				"No memory.");
			return ARCHIVE_FATAL;
		}
		a->client.nodes = 1;
	}

	if (iindex > a->client.nodes - 1)
	{
		archive_set_error(&a->archive, EINVAL,
			"Invalid index specified.");
		return ARCHIVE_FATAL;
	}
	a->client.dataset[iindex].data = client_data;
	a->client.dataset[iindex].begin_position = -1;
	a->client.dataset[iindex].total_size = -1;
	return ARCHIVE_OK;
}