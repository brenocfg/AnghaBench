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
struct sockaddr_dl {int /*<<< orphan*/  sdl_data; } ;
struct ifmaddrs {TYPE_1__* ifma_addr; scalar_t__ ifma_name; struct ifmaddrs* ifma_next; } ;
typedef  scalar_t__ sa_family_t ;
struct TYPE_2__ {scalar_t__ const sa_family; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct ifmaddrs *
next_ifma(struct ifmaddrs *ifma, const char *name, const sa_family_t family)
{

	for(; ifma != NULL; ifma = ifma->ifma_next) {
		struct sockaddr_dl *sdl;

		sdl = (struct sockaddr_dl *)ifma->ifma_name;
		if (ifma->ifma_addr->sa_family == family &&
		    strcmp(sdl->sdl_data, name) == 0)
			break;
	}

	return (ifma);
}