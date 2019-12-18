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
struct iovec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  int ssize_t ;

/* Variables and functions */
 size_t count_iov (struct iovec const*,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 void* realloc (void*,size_t) ; 

ssize_t
iov_to_buf(const struct iovec *iov, int niov, void **buf)
{
	size_t ptr, total;
	int i;

	total = count_iov(iov, niov);
	*buf = realloc(*buf, total);
	if (*buf == NULL)
		return (-1);

	for (i = 0, ptr = 0; i < niov; i++) {
		memcpy(*buf + ptr, iov[i].iov_base, iov[i].iov_len);
		ptr += iov[i].iov_len;
	}

	return (total);
}