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
struct sockaddr_in {int dummy; } ;
struct sockaddr_dl {int dummy; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_LINK 128 

__attribute__((used)) static int
salen(struct sockaddr *sa)
{
	switch (sa->sa_family) {

	case AF_INET:
		return (sizeof(struct sockaddr_in));

	case AF_LINK:
		return (sizeof(struct sockaddr_dl));

	default:
		return (sizeof(struct sockaddr));
	}
}