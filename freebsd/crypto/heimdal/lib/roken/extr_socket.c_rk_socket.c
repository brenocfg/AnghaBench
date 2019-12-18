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

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int SOCK_CLOEXEC ; 
 scalar_t__ errno ; 
 int socket (int,int,int) ; 

int
rk_socket(int domain, int type, int protocol)
{
    int s;
    s = socket (domain, type, protocol);
#ifdef SOCK_CLOEXEC
    if ((SOCK_CLOEXEC & type) && s < 0 && errno == EINVAL) {
	type &= ~SOCK_CLOEXEC;
	s = socket (domain, type, protocol);
    }
#endif
    return s;
}