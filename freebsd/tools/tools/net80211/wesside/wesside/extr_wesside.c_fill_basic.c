#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_frame {scalar_t__ i_dur; scalar_t__ i_seq; int /*<<< orphan*/  i_addr3; int /*<<< orphan*/  i_addr2; int /*<<< orphan*/  i_addr1; } ;
struct TYPE_4__ {int /*<<< orphan*/  psent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bss; } ;

/* Variables and functions */
 unsigned short fnseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned short htole16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mymac ; 
 TYPE_2__ txstate ; 
 TYPE_1__ victim ; 

void fill_basic(struct ieee80211_frame* wh) {
	unsigned short* sp;

	memcpy(wh->i_addr1, victim.bss, 6);
	memcpy(wh->i_addr2, mymac, 6);
	memcpy(wh->i_addr3, victim.bss, 6);

	

	sp = (unsigned short*) wh->i_seq;
	*sp = fnseq(0, txstate.psent);

	sp = (unsigned short*) wh->i_dur;
	*sp = htole16(32767);
}