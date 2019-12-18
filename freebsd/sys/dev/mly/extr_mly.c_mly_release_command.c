#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union mly_command_packet {int dummy; } mly_command_packet ;
struct mly_command {TYPE_2__* mc_packet; int /*<<< orphan*/  mc_packetphys; int /*<<< orphan*/ * mc_private; int /*<<< orphan*/ * mc_complete; scalar_t__ mc_flags; int /*<<< orphan*/ * mc_data; } ;
struct TYPE_3__ {int maximum_sense_size; int /*<<< orphan*/  sense_buffer_address; } ;
struct TYPE_4__ {TYPE_1__ generic; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mly_enqueue_free (struct mly_command*) ; 

__attribute__((used)) static void
mly_release_command(struct mly_command *mc)
{
    debug_called(3);

    /*
     * Fill in parts of the command that may cause confusion if
     * a consumer doesn't when we are later allocated.
     */
    mc->mc_data = NULL;
    mc->mc_flags = 0;
    mc->mc_complete = NULL;
    mc->mc_private = NULL;

    /*
     * By default, we set up to overwrite the command packet with
     * sense information.
     */
    mc->mc_packet->generic.sense_buffer_address = mc->mc_packetphys;
    mc->mc_packet->generic.maximum_sense_size = sizeof(union mly_command_packet);

    mly_enqueue_free(mc);
}