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
struct sshbuf {size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSHBUF_DBG (char*) ; 
 int /*<<< orphan*/  SSHBUF_TELL (char*) ; 
 int SSH_ERR_MESSAGE_INCOMPLETE ; 
 int sshbuf_check_sanity (struct sshbuf*) ; 
 size_t sshbuf_len (struct sshbuf*) ; 

int
sshbuf_consume_end(struct sshbuf *buf, size_t len)
{
	int r;

	SSHBUF_DBG(("len = %zu", len));
	if ((r = sshbuf_check_sanity(buf)) != 0)
		return r;
	if (len == 0)
		return 0;
	if (len > sshbuf_len(buf))
		return SSH_ERR_MESSAGE_INCOMPLETE;
	buf->size -= len;
	SSHBUF_TELL("done");
	return 0;
}