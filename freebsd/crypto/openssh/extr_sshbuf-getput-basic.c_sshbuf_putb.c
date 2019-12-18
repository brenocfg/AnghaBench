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
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sshbuf_len (struct sshbuf const*) ; 
 int /*<<< orphan*/  sshbuf_ptr (struct sshbuf const*) ; 
 int sshbuf_put (struct sshbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sshbuf_putb(struct sshbuf *buf, const struct sshbuf *v)
{
	return sshbuf_put(buf, sshbuf_ptr(v), sshbuf_len(v));
}