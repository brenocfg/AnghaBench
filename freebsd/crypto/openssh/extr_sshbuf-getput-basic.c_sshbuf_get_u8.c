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
typedef  scalar_t__ u_int8_t ;
typedef  scalar_t__ u_char ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int sshbuf_consume (struct sshbuf*,int) ; 
 scalar_t__* sshbuf_ptr (struct sshbuf*) ; 

int
sshbuf_get_u8(struct sshbuf *buf, u_char *valp)
{
	const u_char *p = sshbuf_ptr(buf);
	int r;

	if ((r = sshbuf_consume(buf, 1)) < 0)
		return r;
	if (valp != NULL)
		*valp = (u_int8_t)*p;
	return 0;
}