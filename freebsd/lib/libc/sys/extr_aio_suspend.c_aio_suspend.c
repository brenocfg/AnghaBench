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
struct timespec {int dummy; } ;
struct aiocb {int dummy; } ;

/* Variables and functions */
 size_t INTERPOS_aio_suspend ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (struct aiocb const* const*,int,struct timespec const*) ; 

int
aio_suspend(const struct aiocb * const iocbs[], int niocb,
    const struct timespec *timeout)
{

	return (((int (*)(const struct aiocb * const[], int,
	    const struct timespec *))
	    __libc_interposing[INTERPOS_aio_suspend])(iocbs, niocb, timeout));
}