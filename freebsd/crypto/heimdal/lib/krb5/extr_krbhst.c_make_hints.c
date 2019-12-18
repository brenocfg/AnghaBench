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
struct addrinfo {int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
#define  KRB5_KRBHST_HTTP 130 
#define  KRB5_KRBHST_TCP 129 
#define  KRB5_KRBHST_UDP 128 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
make_hints(struct addrinfo *hints, int proto)
{
    memset(hints, 0, sizeof(*hints));
    hints->ai_family = AF_UNSPEC;
    switch(proto) {
    case KRB5_KRBHST_UDP :
	hints->ai_socktype = SOCK_DGRAM;
	break;
    case KRB5_KRBHST_HTTP :
    case KRB5_KRBHST_TCP :
	hints->ai_socktype = SOCK_STREAM;
	break;
    }
}