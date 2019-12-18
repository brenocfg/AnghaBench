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
typedef  int /*<<< orphan*/  uint32_t ;
struct atiixp_info {int /*<<< orphan*/  blkcnt; } ;
struct atiixp_chinfo {int /*<<< orphan*/  blksz; struct atiixp_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  atiixp_chan_setfragments (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
atiixp_chan_setblocksize(kobj_t obj, void *data, uint32_t blksz)
{
	struct atiixp_chinfo *ch = data;
	struct atiixp_info *sc = ch->parent;

	atiixp_chan_setfragments(obj, data, blksz, sc->blkcnt);

	return (ch->blksz);
}