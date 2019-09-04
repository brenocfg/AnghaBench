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
struct st_headers_early_hints_sender_t {int /*<<< orphan*/  deferred_timeout_entry; } ;

/* Variables and functions */
 scalar_t__ h2o_timer_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_sender_dispose(void *_sender)
{
    struct st_headers_early_hints_sender_t *sender = (struct st_headers_early_hints_sender_t *)_sender;
    if (h2o_timer_is_linked(&sender->deferred_timeout_entry))
        h2o_timer_unlink(&sender->deferred_timeout_entry);
}