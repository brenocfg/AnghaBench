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
struct amr_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amr_enqueue_free (struct amr_command*) ; 
 int /*<<< orphan*/  debug_called (int) ; 

void
amr_releasecmd(struct amr_command *ac)
{
    debug_called(3);

    amr_enqueue_free(ac);
}