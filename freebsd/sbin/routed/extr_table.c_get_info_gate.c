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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; scalar_t__ sin_family; TYPE_1__ sin_addr; } ;
struct sockaddr_dl {scalar_t__ sdl_family; int /*<<< orphan*/  sdl_index; } ;
struct sockaddr {int dummy; } ;
struct interface {int /*<<< orphan*/  int_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_LINK ; 
 struct interface* ifwithindex (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
get_info_gate(struct sockaddr **sap,
	      struct sockaddr_in *rsin)
{
	struct sockaddr_dl *sdl = (struct sockaddr_dl *)*sap;
	struct interface *ifp;

	if (sdl == NULL)
		return 0;
	if ((sdl)->sdl_family == AF_INET)
		return 1;
	if ((sdl)->sdl_family != AF_LINK)
		return 0;

	ifp = ifwithindex(sdl->sdl_index, 1);
	if (ifp == NULL)
		return 0;

	rsin->sin_addr.s_addr = ifp->int_addr;
#ifdef _HAVE_SA_LEN
	rsin->sin_len = sizeof(*rsin);
#endif
	rsin->sin_family = AF_INET;
	*sap = (struct sockaddr*)rsin;

	return 1;
}