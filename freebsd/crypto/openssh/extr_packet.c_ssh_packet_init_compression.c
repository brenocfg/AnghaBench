#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ssh {TYPE_1__* state; } ;
struct TYPE_2__ {int /*<<< orphan*/ * compression_buffer; } ;

/* Variables and functions */
 int SSH_ERR_ALLOC_FAIL ; 
 int /*<<< orphan*/ * sshbuf_new () ; 

__attribute__((used)) static int
ssh_packet_init_compression(struct ssh *ssh)
{
	if (!ssh->state->compression_buffer &&
	   ((ssh->state->compression_buffer = sshbuf_new()) == NULL))
		return SSH_ERR_ALLOC_FAIL;
	return 0;
}