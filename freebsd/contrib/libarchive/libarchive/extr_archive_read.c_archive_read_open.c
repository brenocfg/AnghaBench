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
typedef  int /*<<< orphan*/  archive_read_callback ;
typedef  int /*<<< orphan*/  archive_open_callback ;
typedef  int /*<<< orphan*/  archive_close_callback ;

/* Variables and functions */
 int archive_read_open1 (struct archive*) ; 
 int /*<<< orphan*/  archive_read_set_callback_data (struct archive*,void*) ; 
 int /*<<< orphan*/  archive_read_set_close_callback (struct archive*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_set_open_callback (struct archive*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_set_read_callback (struct archive*,int /*<<< orphan*/ *) ; 

int
archive_read_open(struct archive *a, void *client_data,
    archive_open_callback *client_opener, archive_read_callback *client_reader,
    archive_close_callback *client_closer)
{
	/* Old archive_read_open() is just a thin shell around
	 * archive_read_open1. */
	archive_read_set_open_callback(a, client_opener);
	archive_read_set_read_callback(a, client_reader);
	archive_read_set_close_callback(a, client_closer);
	archive_read_set_callback_data(a, client_data);
	return archive_read_open1(a);
}