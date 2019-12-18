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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sc_chinfo {scalar_t__ dir; int /*<<< orphan*/  speed; scalar_t__ dma_active; struct sc_info* parent; } ;
struct sc_info {struct sc_chinfo pch; struct sc_chinfo rch; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 scalar_t__ PCMDIR_PLAY ; 

__attribute__((used)) static u_int32_t
alschan_setspeed(kobj_t obj, void *data, u_int32_t speed)
{
	struct	sc_chinfo *ch = data, *other;
	struct  sc_info *sc = ch->parent;

	other = (ch->dir == PCMDIR_PLAY) ? &sc->rch : &sc->pch;

	/* Deny request if other dma channel is active */
	if (other->dma_active) {
		ch->speed = other->speed;
		return other->speed;
	}

	ch->speed = speed;
	return speed;
}