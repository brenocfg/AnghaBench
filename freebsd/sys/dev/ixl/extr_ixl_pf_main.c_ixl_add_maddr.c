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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr_dl {int dummy; } ;
struct ixl_vsi {int dummy; } ;

/* Variables and functions */
 scalar_t__ LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  ixl_add_mc_filter (struct ixl_vsi*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_int
ixl_add_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct ixl_vsi *vsi = arg;

	ixl_add_mc_filter(vsi, (u8*)LLADDR(sdl));

	return (1);
}