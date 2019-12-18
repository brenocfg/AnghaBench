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
struct iovec {scalar_t__ iov_len; } ;

/* Variables and functions */

size_t
count_iov(const struct iovec *iov, int niov)
{
	size_t total = 0;
	int i;

	for (i = 0; i < niov; i++)
		total += iov[i].iov_len;

	return (total);
}