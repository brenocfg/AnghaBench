#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct archive {int dummy; } ;

/* Variables and functions */
 int archive_read_set_callback_data2 (struct archive*,void*,int /*<<< orphan*/ ) ; 

int
archive_read_set_callback_data(struct archive *_a, void *client_data)
{
	return archive_read_set_callback_data2(_a, client_data, 0);
}