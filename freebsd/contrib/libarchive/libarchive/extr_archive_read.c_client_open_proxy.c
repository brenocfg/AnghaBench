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
struct archive_read_filter {int /*<<< orphan*/  data; TYPE_2__* archive; } ;
struct archive {int dummy; } ;
struct TYPE_3__ {int (* opener ) (struct archive*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ client; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int stub1 (struct archive*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
client_open_proxy(struct archive_read_filter *self)
{
  int r = ARCHIVE_OK;
	if (self->archive->client.opener != NULL)
		r = (self->archive->client.opener)(
		    (struct archive *)self->archive, self->data);
	return (r);
}