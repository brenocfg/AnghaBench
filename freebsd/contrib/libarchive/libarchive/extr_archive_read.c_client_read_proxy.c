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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* reader ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const**) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  archive; TYPE_1__ client; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const**) ; 

__attribute__((used)) static ssize_t
client_read_proxy(struct archive_read_filter *self, const void **buff)
{
	ssize_t r;
	r = (self->archive->client.reader)(&self->archive->archive,
	    self->data, buff);
	return (r);
}