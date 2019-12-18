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
struct kiocb {int dummy; } ;
struct iov_iter {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EFAULT ; 
 size_t ERESTARTSYS ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 size_t iov_iter_zero (size_t,struct iov_iter*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t read_iter_zero(struct kiocb *iocb, struct iov_iter *iter)
{
	size_t written = 0;

	while (iov_iter_count(iter)) {
		size_t chunk = iov_iter_count(iter), n;

		if (chunk > PAGE_SIZE)
			chunk = PAGE_SIZE;	/* Just for latency reasons */
		n = iov_iter_zero(chunk, iter);
		if (!n && iov_iter_count(iter))
			return written ? written : -EFAULT;
		written += n;
		if (signal_pending(current))
			return written ? written : -ERESTARTSYS;
		cond_resched();
	}
	return written;
}