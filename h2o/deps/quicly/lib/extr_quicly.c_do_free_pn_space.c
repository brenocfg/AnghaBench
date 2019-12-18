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
struct st_quicly_pn_space_t {int /*<<< orphan*/  ack_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct st_quicly_pn_space_t*) ; 
 int /*<<< orphan*/  quicly_ranges_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_free_pn_space(struct st_quicly_pn_space_t *space)
{
    quicly_ranges_clear(&space->ack_queue);
    free(space);
}