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
struct iovec {int /*<<< orphan*/  iov_base; int /*<<< orphan*/  iov_len; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t MIN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  free (struct iovec*) ; 
 struct iovec* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  seek_iov (struct iovec*,int,struct iovec*,int*,size_t) ; 

ssize_t
buf_to_iov(const void *buf, size_t buflen, struct iovec *iov, int niov,
    size_t seek)
{
	struct iovec *diov;
	int ndiov, i;
	size_t off = 0, len;

	if (seek > 0) {
		diov = malloc(sizeof(struct iovec) * niov);
		seek_iov(iov, niov, diov, &ndiov, seek);
	} else {
		diov = iov;
		ndiov = niov;
	}

	for (i = 0; i < ndiov && off < buflen; i++) {
		len = MIN(diov[i].iov_len, buflen - off);
		memcpy(diov[i].iov_base, buf + off, len);
		off += len;
	}

	if (seek > 0)
		free(diov);

	return ((ssize_t)off);
}