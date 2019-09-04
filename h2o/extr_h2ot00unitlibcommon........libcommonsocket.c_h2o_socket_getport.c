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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int sa_family; } ;
typedef  int int32_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int htons (int /*<<< orphan*/ ) ; 

int32_t h2o_socket_getport(struct sockaddr *sa)
{
    switch (sa->sa_family) {
    case AF_INET:
        return htons(((struct sockaddr_in *)sa)->sin_port);
    case AF_INET6:
        return htons(((struct sockaddr_in6 *)sa)->sin6_port);
    default:
        return -1;
    }
}