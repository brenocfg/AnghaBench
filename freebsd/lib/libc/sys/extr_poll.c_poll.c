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
struct pollfd {int dummy; } ;
typedef  int /*<<< orphan*/  nfds_t ;

/* Variables and functions */
 size_t INTERPOS_poll ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (struct pollfd*,int /*<<< orphan*/ ,int) ; 

int
poll(struct pollfd pfd[], nfds_t nfds, int timeout)
{

	return (((int (*)(struct pollfd *, nfds_t, int))
	    __libc_interposing[INTERPOS_poll])(pfd, nfds, timeout));
}