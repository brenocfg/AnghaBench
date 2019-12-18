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
struct iovec {struct iovec* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct iovec*) ; 

void
free_iovec(struct iovec **iov, int *iovlen)
{
	int i;

	for (i = 0; i < *iovlen; i++)
		free((*iov)[i].iov_base);
	free(*iov);
}