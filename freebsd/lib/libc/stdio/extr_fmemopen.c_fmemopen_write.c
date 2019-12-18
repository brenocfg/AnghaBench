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
struct fmemopen_cookie {int size; int off; char* buf; int len; int /*<<< orphan*/  bin; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static int
fmemopen_write(void *cookie, const char *buf, int nbytes)
{
	struct fmemopen_cookie *ck = cookie;

	if (nbytes > ck->size - ck->off)
		nbytes = ck->size - ck->off;

	if (nbytes == 0)
		return (0);

	memcpy(ck->buf + ck->off, buf, nbytes);

	ck->off += nbytes;

	if (ck->off > ck->len)
		ck->len = ck->off;

	/*
	 * We append a NULL byte if all these conditions are met:
	 * - the buffer is not binary
	 * - the buffer is not full
	 * - the data just written doesn't already end with a NULL byte
	 */
	if (!ck->bin && ck->off < ck->size && ck->buf[ck->off - 1] != '\0')
		ck->buf[ck->off] = '\0';

	return (nbytes);
}