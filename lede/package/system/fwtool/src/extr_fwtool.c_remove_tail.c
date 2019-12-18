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
struct data_buf {int file_len; scalar_t__ cur_len; int /*<<< orphan*/ * prev; int /*<<< orphan*/ * cur; } ;

/* Variables and functions */
 scalar_t__ BUFLEN ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
remove_tail(struct data_buf *dbuf, int len)
{
	dbuf->cur_len -= len;
	dbuf->file_len -= len;

	if (dbuf->cur_len)
		return;

	free(dbuf->cur);
	dbuf->cur = dbuf->prev;
	dbuf->prev = NULL;
	dbuf->cur_len = BUFLEN;
}