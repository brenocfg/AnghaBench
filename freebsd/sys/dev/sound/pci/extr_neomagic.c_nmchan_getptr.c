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
typedef  scalar_t__ u_int32_t ;
struct sc_info {scalar_t__ rbuf; scalar_t__ pbuf; } ;
struct sc_chinfo {scalar_t__ dir; struct sc_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  NM_PBUFFER_CURRP ; 
 int /*<<< orphan*/  NM_RBUFFER_CURRP ; 
 scalar_t__ PCMDIR_PLAY ; 
 scalar_t__ nm_rd (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u_int32_t
nmchan_getptr(kobj_t obj, void *data)
{
	struct sc_chinfo *ch = data;
	struct sc_info *sc = ch->parent;

	if (ch->dir == PCMDIR_PLAY)
		return nm_rd(sc, NM_PBUFFER_CURRP, 4) - sc->pbuf;
	else
		return nm_rd(sc, NM_RBUFFER_CURRP, 4) - sc->rbuf;
}