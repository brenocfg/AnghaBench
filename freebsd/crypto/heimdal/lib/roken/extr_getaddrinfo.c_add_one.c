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
struct addrinfo {int ai_protocol; int ai_socktype; char* ai_canonname; struct addrinfo* ai_next; scalar_t__ ai_flags; } ;

/* Variables and functions */
 int EAI_MEMORY ; 
 int /*<<< orphan*/  free (struct addrinfo*) ; 
 struct addrinfo* malloc (int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct addrinfo*,void*,int) ; 

__attribute__((used)) static int
add_one (int port, int protocol, int socktype,
	 struct addrinfo ***ptr,
	 int (*func)(struct addrinfo *, void *data, int port),
	 void *data,
	 char *canonname)
{
    struct addrinfo *a;
    int ret;

    a = malloc (sizeof (*a));
    if (a == NULL)
	return EAI_MEMORY;
    memset (a, 0, sizeof(*a));
    a->ai_flags     = 0;
    a->ai_next      = NULL;
    a->ai_protocol  = protocol;
    a->ai_socktype  = socktype;
    a->ai_canonname = canonname;
    ret = (*func)(a, data, port);
    if (ret) {
	free (a);
	return ret;
    }
    **ptr = a;
    *ptr = &a->ai_next;
    return 0;
}