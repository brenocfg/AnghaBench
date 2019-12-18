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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  quicly_ranges_t ;

/* Variables and functions */
 int insert_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_ranges_init (int /*<<< orphan*/ *) ; 

int quicly_ranges_init_with_range(quicly_ranges_t *ranges, uint64_t start, uint64_t end)
{
    quicly_ranges_init(ranges);
    return insert_at(ranges, start, end, 0);
}