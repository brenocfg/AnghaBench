#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sin6_scope_id; void* sin6_port; } ;
struct TYPE_5__ {void* sin_port; } ;
struct TYPE_4__ {int sa_family; } ;
union sktaddr {TYPE_3__ s6; TYPE_2__ s4; TYPE_1__ s; } ;
typedef  void* __be16 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EINVAL ; 

__attribute__((used)) static int set_link_port(union sktaddr *s, __be16 port, int oif)
{
	switch (s->s.sa_family) {
	case AF_INET:
		s->s4.sin_port = port;
		break;
	case AF_INET6:
		s->s6.sin6_port = port;
		s->s6.sin6_scope_id = oif;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}