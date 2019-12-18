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
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 struct iovec* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct iovec *
getcopy(struct iovec *iov, int n)
{
	struct iovec *tiov;
	int i;

	tiov = malloc(n * sizeof(struct iovec), M_DEVBUF, M_NOWAIT);
	for (i = 0; i < n; i++) {
		tiov[i].iov_base = iov[i].iov_base;
		tiov[i].iov_len = iov[i].iov_len;
	}

	return (tiov);
}