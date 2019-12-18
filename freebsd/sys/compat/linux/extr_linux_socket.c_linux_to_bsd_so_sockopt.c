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
#define  LINUX_SO_ACCEPTCONN 145 
#define  LINUX_SO_BROADCAST 144 
#define  LINUX_SO_DEBUG 143 
#define  LINUX_SO_DONTROUTE 142 
#define  LINUX_SO_ERROR 141 
#define  LINUX_SO_KEEPALIVE 140 
#define  LINUX_SO_LINGER 139 
#define  LINUX_SO_OOBINLINE 138 
#define  LINUX_SO_PEERCRED 137 
#define  LINUX_SO_RCVBUF 136 
#define  LINUX_SO_RCVLOWAT 135 
#define  LINUX_SO_RCVTIMEO 134 
#define  LINUX_SO_REUSEADDR 133 
#define  LINUX_SO_SNDBUF 132 
#define  LINUX_SO_SNDLOWAT 131 
#define  LINUX_SO_SNDTIMEO 130 
#define  LINUX_SO_TIMESTAMP 129 
#define  LINUX_SO_TYPE 128 
 int LOCAL_PEERCRED ; 
 int SO_ACCEPTCONN ; 
 int SO_BROADCAST ; 
 int SO_DEBUG ; 
 int SO_DONTROUTE ; 
 int SO_ERROR ; 
 int SO_KEEPALIVE ; 
 int SO_LINGER ; 
 int SO_OOBINLINE ; 
 int SO_RCVBUF ; 
 int SO_RCVLOWAT ; 
 int SO_RCVTIMEO ; 
 int SO_REUSEADDR ; 
 int SO_SNDBUF ; 
 int SO_SNDLOWAT ; 
 int SO_SNDTIMEO ; 
 int SO_TIMESTAMP ; 
 int SO_TYPE ; 

__attribute__((used)) static int
linux_to_bsd_so_sockopt(int opt)
{

	switch (opt) {
	case LINUX_SO_DEBUG:
		return (SO_DEBUG);
	case LINUX_SO_REUSEADDR:
		return (SO_REUSEADDR);
	case LINUX_SO_TYPE:
		return (SO_TYPE);
	case LINUX_SO_ERROR:
		return (SO_ERROR);
	case LINUX_SO_DONTROUTE:
		return (SO_DONTROUTE);
	case LINUX_SO_BROADCAST:
		return (SO_BROADCAST);
	case LINUX_SO_SNDBUF:
		return (SO_SNDBUF);
	case LINUX_SO_RCVBUF:
		return (SO_RCVBUF);
	case LINUX_SO_KEEPALIVE:
		return (SO_KEEPALIVE);
	case LINUX_SO_OOBINLINE:
		return (SO_OOBINLINE);
	case LINUX_SO_LINGER:
		return (SO_LINGER);
	case LINUX_SO_PEERCRED:
		return (LOCAL_PEERCRED);
	case LINUX_SO_RCVLOWAT:
		return (SO_RCVLOWAT);
	case LINUX_SO_SNDLOWAT:
		return (SO_SNDLOWAT);
	case LINUX_SO_RCVTIMEO:
		return (SO_RCVTIMEO);
	case LINUX_SO_SNDTIMEO:
		return (SO_SNDTIMEO);
	case LINUX_SO_TIMESTAMP:
		return (SO_TIMESTAMP);
	case LINUX_SO_ACCEPTCONN:
		return (SO_ACCEPTCONN);
	}
	return (-1);
}