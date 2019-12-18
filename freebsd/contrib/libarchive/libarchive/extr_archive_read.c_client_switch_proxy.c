#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct archive_read_filter {void* data; TYPE_3__* archive; } ;
struct archive {int dummy; } ;
struct TYPE_5__ {unsigned int cursor; int (* switcher ) (struct archive*,void*,void*) ;int (* closer ) (struct archive*,void*) ;int (* opener ) (struct archive*,void*) ;TYPE_1__* dataset; } ;
struct TYPE_6__ {TYPE_2__ client; } ;
struct TYPE_4__ {void* data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int stub1 (struct archive*,void*,void*) ; 
 int stub2 (struct archive*,void*) ; 
 int stub3 (struct archive*,void*) ; 

__attribute__((used)) static int
client_switch_proxy(struct archive_read_filter *self, unsigned int iindex)
{
  int r1 = ARCHIVE_OK, r2 = ARCHIVE_OK;
	void *data2 = NULL;

	/* Don't do anything if already in the specified data node */
	if (self->archive->client.cursor == iindex)
		return (ARCHIVE_OK);

	self->archive->client.cursor = iindex;
	data2 = self->archive->client.dataset[self->archive->client.cursor].data;
	if (self->archive->client.switcher != NULL)
	{
		r1 = r2 = (self->archive->client.switcher)
			((struct archive *)self->archive, self->data, data2);
		self->data = data2;
	}
	else
	{
		/* Attempt to call close and open instead */
		if (self->archive->client.closer != NULL)
			r1 = (self->archive->client.closer)
				((struct archive *)self->archive, self->data);
		self->data = data2;
		if (self->archive->client.opener != NULL)
			r2 = (self->archive->client.opener)
				((struct archive *)self->archive, self->data);
	}
	return (r1 < r2) ? r1 : r2;
}