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
#define  LINUX_TCP_KEEPCNT 133 
#define  LINUX_TCP_KEEPIDLE 132 
#define  LINUX_TCP_KEEPINTVL 131 
#define  LINUX_TCP_MAXSEG 130 
#define  LINUX_TCP_MD5SIG 129 
#define  LINUX_TCP_NODELAY 128 
 int TCP_KEEPCNT ; 
 int TCP_KEEPIDLE ; 
 int TCP_KEEPINTVL ; 
 int TCP_MAXSEG ; 
 int TCP_MD5SIG ; 
 int TCP_NODELAY ; 

__attribute__((used)) static int
linux_to_bsd_tcp_sockopt(int opt)
{

	switch (opt) {
	case LINUX_TCP_NODELAY:
		return (TCP_NODELAY);
	case LINUX_TCP_MAXSEG:
		return (TCP_MAXSEG);
	case LINUX_TCP_KEEPIDLE:
		return (TCP_KEEPIDLE);
	case LINUX_TCP_KEEPINTVL:
		return (TCP_KEEPINTVL);
	case LINUX_TCP_KEEPCNT:
		return (TCP_KEEPCNT);
	case LINUX_TCP_MD5SIG:
		return (TCP_MD5SIG);
	}
	return (-1);
}