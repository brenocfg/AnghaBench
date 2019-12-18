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
struct TYPE_4__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  buffer; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  buffer; } ;
struct sb_info {TYPE_2__ rch; TYPE_1__ pch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_DATA_AVAIL ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_lock (struct sb_info*) ; 
 int /*<<< orphan*/  sb_rd (struct sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_unlock (struct sb_info*) ; 
 scalar_t__ sndbuf_runsz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sb_intr(void *arg)
{
    	struct sb_info *sb = (struct sb_info *)arg;

	sb_lock(sb);
    	if (sndbuf_runsz(sb->pch.buffer) > 0) {
		sb_unlock(sb);
		chn_intr(sb->pch.channel);
		sb_lock(sb);
	}

    	if (sndbuf_runsz(sb->rch.buffer) > 0) {
		sb_unlock(sb);
		chn_intr(sb->rch.channel);
		sb_lock(sb);
	}

	sb_rd(sb, DSP_DATA_AVAIL); /* int ack */
	sb_unlock(sb);
}