#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct TYPE_3__ {int length; int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  GSS_C_AF_INET ; 
 int /*<<< orphan*/  GSS_C_AF_INET6 ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 

__attribute__((used)) static void
sockaddr_to_gss_address (struct sockaddr *sa,
			 OM_uint32 *addr_type,
			 gss_buffer_desc *gss_addr)
{
    switch (sa->sa_family) {
#ifdef HAVE_IPV6
    case AF_INET6 : {
	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;

	gss_addr->length = 16;
	gss_addr->value  = &sin6->sin6_addr;
	*addr_type       = GSS_C_AF_INET6;
	break;
    }
#endif
    case AF_INET : {
	struct sockaddr_in *sin4 = (struct sockaddr_in *)sa;

	gss_addr->length = 4;
	gss_addr->value  = &sin4->sin_addr;
	*addr_type       = GSS_C_AF_INET;
	break;
    }
    default :
	errx (1, "unknown address family %d", sa->sa_family);

    }
}