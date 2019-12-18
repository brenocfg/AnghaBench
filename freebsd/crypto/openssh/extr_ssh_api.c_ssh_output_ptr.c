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
typedef  int /*<<< orphan*/  u_char ;
struct sshbuf {int dummy; } ;
struct ssh {int dummy; } ;

/* Variables and functions */
 struct sshbuf* ssh_packet_get_output (struct ssh*) ; 
 size_t sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/  const* sshbuf_ptr (struct sshbuf*) ; 

const u_char *
ssh_output_ptr(struct ssh *ssh, size_t *len)
{
	struct sshbuf *output = ssh_packet_get_output(ssh);

	*len = sshbuf_len(output);
	return sshbuf_ptr(output);
}