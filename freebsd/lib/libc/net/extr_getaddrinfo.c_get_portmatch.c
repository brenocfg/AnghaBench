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
struct addrinfo {int dummy; } ;

/* Variables and functions */
 int get_port (struct addrinfo*,char const*,int) ; 

__attribute__((used)) static int
get_portmatch(const struct addrinfo *ai, const char *servname)
{

	/* get_port does not touch first argument when matchonly == 1. */
	/* LINTED const cast */
	return get_port((struct addrinfo *)ai, servname, 1);
}