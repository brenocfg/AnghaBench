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
struct ssh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ssh_packet_get_input (struct ssh*) ; 
 scalar_t__ sshbuf_check_reserve (int /*<<< orphan*/ ,size_t) ; 

int
ssh_input_space(struct ssh *ssh, size_t len)
{
	return (0 == sshbuf_check_reserve(ssh_packet_get_input(ssh), len));
}