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
struct sshbuf {int refcount; size_t max_size; size_t size; size_t off; scalar_t__ readonly; } ;

/* Variables and functions */
 scalar_t__ sshbuf_check_sanity (struct sshbuf const*) ; 

size_t
sshbuf_avail(const struct sshbuf *buf)
{
	if (sshbuf_check_sanity(buf) != 0 || buf->readonly || buf->refcount > 1)
		return 0;
	return buf->max_size - (buf->size - buf->off);
}