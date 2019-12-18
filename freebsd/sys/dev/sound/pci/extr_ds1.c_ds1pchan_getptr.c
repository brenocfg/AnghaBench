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
typedef  int u_int32_t ;
struct sc_pchinfo {int fmt; struct pbank* lslot; struct sc_info* parent; } ;
struct sc_info {int currbank; } ;
struct pbank {int PgStart; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AFMT_16BIT ; 
 int AFMT_CHANNEL (int) ; 

__attribute__((used)) static u_int32_t
ds1pchan_getptr(kobj_t obj, void *data)
{
	struct sc_pchinfo *ch = data;
	struct sc_info *sc = ch->parent;
	volatile struct pbank *bank;
	int ss;
	u_int32_t ptr;

	ss = (AFMT_CHANNEL(ch->fmt) > 1)? 1 : 0;
	ss += (ch->fmt & AFMT_16BIT)? 1 : 0;

	bank = ch->lslot + sc->currbank;
	/* printf("getptr: %d\n", bank->PgStart << ss); */
	ptr = bank->PgStart;
	ptr <<= ss;
	return ptr;
}