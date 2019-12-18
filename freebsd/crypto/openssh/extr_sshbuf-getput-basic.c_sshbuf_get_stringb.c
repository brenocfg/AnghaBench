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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int sshbuf_get (struct sshbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sshbuf_get_u32 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int sshbuf_peek_string_direct (struct sshbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sshbuf_reserve (struct sshbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int
sshbuf_get_stringb(struct sshbuf *buf, struct sshbuf *v)
{
	u_int32_t len;
	u_char *p;
	int r;

	/*
	 * Use sshbuf_peek_string_direct() to figure out if there is
	 * a complete string in 'buf' and copy the string directly
	 * into 'v'.
	 */
	if ((r = sshbuf_peek_string_direct(buf, NULL, NULL)) != 0 ||
	    (r = sshbuf_get_u32(buf, &len)) != 0 ||
	    (r = sshbuf_reserve(v, len, &p)) != 0 ||
	    (r = sshbuf_get(buf, p, len)) != 0)
		return r;
	return 0;
}