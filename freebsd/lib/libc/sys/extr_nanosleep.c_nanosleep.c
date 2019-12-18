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

/* Variables and functions */
 size_t INTERPOS_nanosleep ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (struct timespec const*,struct timespec*) ; 

int
nanosleep(const struct timespec *rqtp, struct timespec *rmtp)
{

	return (((int (*)(const struct timespec *, struct timespec *))
	    __libc_interposing[INTERPOS_nanosleep])(rqtp, rmtp));
}