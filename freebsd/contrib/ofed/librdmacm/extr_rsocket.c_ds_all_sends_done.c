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
struct rsocket {scalar_t__ sqe_avail; scalar_t__ sq_size; } ;

/* Variables and functions */

__attribute__((used)) static int ds_all_sends_done(struct rsocket *rs)
{
	return rs->sqe_avail == rs->sq_size;
}