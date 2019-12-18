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
struct fmemopen_cookie {int len; int off; int buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int,int) ; 

__attribute__((used)) static int
fmemopen_read(void *cookie, char *buf, int nbytes)
{
	struct fmemopen_cookie *ck = cookie;

	if (nbytes > ck->len - ck->off)
		nbytes = ck->len - ck->off;

	if (nbytes == 0)
		return (0);

	memcpy(buf, ck->buf + ck->off, nbytes);

	ck->off += nbytes;

	return (nbytes);
}