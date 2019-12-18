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
 int sshbuf_put_cstring (struct sshbuf*,char const*) ; 
 int sshbuf_put_u8 (struct sshbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
serialise_nullable_string(struct sshbuf *m, const char *s)
{
	int r;

	if ((r = sshbuf_put_u8(m, s == NULL)) != 0 ||
	    (r = sshbuf_put_cstring(m, s)) != 0)
		return r;
	return 0;
}