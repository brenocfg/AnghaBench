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
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_dl {int sdl_len; int /*<<< orphan*/  sdl_type; int /*<<< orphan*/  sdl_index; int /*<<< orphan*/  sdl_family; } ;
struct sockaddr {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LINK ; 
 int /*<<< orphan*/  memset (struct sockaddr_dl*,int /*<<< orphan*/ ,int) ; 

struct sockaddr_dl *
link_init_sdl(struct ifnet *ifp, struct sockaddr *paddr, u_char iftype)
{
	struct sockaddr_dl *sdl;

	sdl = (struct sockaddr_dl *)paddr;
	memset(sdl, 0, sizeof(struct sockaddr_dl));
	sdl->sdl_len = sizeof(struct sockaddr_dl);
	sdl->sdl_family = AF_LINK;
	sdl->sdl_index = ifp->if_index;
	sdl->sdl_type = iftype;

	return (sdl);
}