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
struct atiixp_info {scalar_t__ polling; } ;
struct atiixp_chinfo {int /*<<< orphan*/  ptr; struct atiixp_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  atiixp_dmapos (struct atiixp_chinfo*) ; 
 int /*<<< orphan*/  atiixp_lock (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_unlock (struct atiixp_info*) ; 

__attribute__((used)) static uint32_t
atiixp_chan_getptr(kobj_t obj, void *data)
{
	struct atiixp_chinfo *ch = data;
	struct atiixp_info *sc = ch->parent;
	uint32_t ptr;

	atiixp_lock(sc);
	if (sc->polling != 0)
		ptr = ch->ptr;
	else
		ptr = atiixp_dmapos(ch);
	atiixp_unlock(sc);

	return (ptr);
}