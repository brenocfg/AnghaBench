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
struct archive_read {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,size_t) ; 

__attribute__((used)) static void
tar_flush_unconsumed(struct archive_read *a, size_t *unconsumed)
{
	if (*unconsumed) {
/*
		void *data = (void *)__archive_read_ahead(a, *unconsumed, NULL);
		 * this block of code is to poison claimed unconsumed space, ensuring
		 * things break if it is in use still.
		 * currently it WILL break things, so enable it only for debugging this issue
		if (data) {
			memset(data, 0xff, *unconsumed);
		}
*/
		__archive_read_consume(a, *unconsumed);
		*unconsumed = 0;
	}
}