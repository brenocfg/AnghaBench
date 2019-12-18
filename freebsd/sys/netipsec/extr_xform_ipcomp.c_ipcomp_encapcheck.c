#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ sa_family; } ;
union sockaddr_union {TYPE_1__ sa; } ;
struct secasvar {int dummy; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IPPROTO_IPCOMP ; 
 struct secasvar* key_allocsa_tunnel (union sockaddr_union*,union sockaddr_union*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_freesav (struct secasvar**) ; 

__attribute__((used)) static int
ipcomp_encapcheck(union sockaddr_union *src, union sockaddr_union *dst)
{
	struct secasvar *sav;

	sav = key_allocsa_tunnel(src, dst, IPPROTO_IPCOMP);
	if (sav == NULL)
		return (0);
	key_freesav(&sav);

	if (src->sa.sa_family == AF_INET)
		return (sizeof(struct in_addr) << 4);
	else
		return (sizeof(struct in6_addr) << 4);
}