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
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PEEK_U16 (int /*<<< orphan*/  const*) ; 
 int sshbuf_consume (struct sshbuf*,int) ; 
 int /*<<< orphan*/ * sshbuf_ptr (struct sshbuf*) ; 

int
sshbuf_get_u16(struct sshbuf *buf, u_int16_t *valp)
{
	const u_char *p = sshbuf_ptr(buf);
	int r;

	if ((r = sshbuf_consume(buf, 2)) < 0)
		return r;
	if (valp != NULL)
		*valp = PEEK_U16(p);
	return 0;
}