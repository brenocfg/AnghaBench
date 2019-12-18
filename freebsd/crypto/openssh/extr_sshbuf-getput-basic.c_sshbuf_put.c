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
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 int sshbuf_reserve (struct sshbuf*,size_t,int /*<<< orphan*/ **) ; 

int
sshbuf_put(struct sshbuf *buf, const void *v, size_t len)
{
	u_char *p;
	int r;

	if ((r = sshbuf_reserve(buf, len, &p)) < 0)
		return r;
	if (len != 0)
		memcpy(p, v, len);
	return 0;
}