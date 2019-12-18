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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,size_t) ; 
 int sshbuf_consume (struct sshbuf*,size_t) ; 
 int /*<<< orphan*/ * sshbuf_ptr (struct sshbuf*) ; 

int
sshbuf_get(struct sshbuf *buf, void *v, size_t len)
{
	const u_char *p = sshbuf_ptr(buf);
	int r;

	if ((r = sshbuf_consume(buf, len)) < 0)
		return r;
	if (v != NULL && len != 0)
		memcpy(v, p, len);
	return 0;
}