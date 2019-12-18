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
struct buf {struct buf* buf; struct buf* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct buf*) ; 

__attribute__((used)) static void
free_buf_list(struct buf *buf)
{
	struct buf *tmp;

	while (buf != NULL) {
		tmp = buf;
		buf = tmp->next;
		free(tmp->buf);
		free(tmp);
	}
}