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
 int /*<<< orphan*/ * __archive_read_ahead (struct archive_read*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
archive_read_format_empty_bid(struct archive_read *a, int best_bid)
{
	if (best_bid < 1 && __archive_read_ahead(a, 1, NULL) == NULL)
		return (1);
	return (-1);
}