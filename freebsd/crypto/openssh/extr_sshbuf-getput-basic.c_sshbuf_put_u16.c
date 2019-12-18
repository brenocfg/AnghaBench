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
 int /*<<< orphan*/  POKE_U16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sshbuf_reserve (struct sshbuf*,int,int /*<<< orphan*/ **) ; 

int
sshbuf_put_u16(struct sshbuf *buf, u_int16_t val)
{
	u_char *p;
	int r;

	if ((r = sshbuf_reserve(buf, 2, &p)) < 0)
		return r;
	POKE_U16(p, val);
	return 0;
}