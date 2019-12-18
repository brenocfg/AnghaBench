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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;
struct ecore_mcast_list_elem {int /*<<< orphan*/ * mac; } ;

/* Variables and functions */
 scalar_t__ LLADDR (struct sockaddr_dl*) ; 

__attribute__((used)) static u_int
bxe_push_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
    struct ecore_mcast_list_elem *mc_mac = arg;

    mc_mac += cnt;
    mc_mac->mac = (uint8_t *)LLADDR(sdl);

    return (1);
}