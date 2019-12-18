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
struct TYPE_2__ {int /*<<< orphan*/  nodes; } ;
struct archive_read {TYPE_1__ client; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int archive_read_add_callback_data (struct archive*,void*,int /*<<< orphan*/ ) ; 

int
archive_read_append_callback_data(struct archive *_a, void *client_data)
{
	struct archive_read *a = (struct archive_read *)_a;
	return archive_read_add_callback_data(_a, client_data, a->client.nodes);
}