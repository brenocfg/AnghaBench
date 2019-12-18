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
struct _citrus_lookup {int dummy; } ;

/* Variables and functions */
 scalar_t__ seq_next_plain (struct _citrus_lookup*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
seq_get_num_entries_plain(struct _citrus_lookup *cl)
{
	int num;

	num = 0;
	while (seq_next_plain(cl, NULL, NULL) == 0)
		num++;

	return (num);
}