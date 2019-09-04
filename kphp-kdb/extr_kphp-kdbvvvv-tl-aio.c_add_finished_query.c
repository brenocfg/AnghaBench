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
struct tl_saved_query {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  finished_aio_queue ; 
 int /*<<< orphan*/  queue_add_finished_aio (int /*<<< orphan*/ ,struct tl_saved_query*) ; 

void add_finished_query (struct tl_saved_query *q) {
  finished_aio_queue = queue_add_finished_aio (finished_aio_queue, q);
}