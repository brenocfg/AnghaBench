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
struct xsockbuf {int /*<<< orphan*/  sb_timeo; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_lowat; int /*<<< orphan*/  sb_mbmax; int /*<<< orphan*/  sb_ccnt; int /*<<< orphan*/  sb_mcnt; int /*<<< orphan*/  sb_mbcnt; int /*<<< orphan*/  sb_hiwat; int /*<<< orphan*/  sb_cc; } ;
struct sockbuf {int /*<<< orphan*/  sb_timeo; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_lowat; int /*<<< orphan*/  sb_mbmax; int /*<<< orphan*/  sb_ccnt; int /*<<< orphan*/  sb_mcnt; int /*<<< orphan*/  sb_mbcnt; int /*<<< orphan*/  sb_hiwat; int /*<<< orphan*/  sb_ccc; } ;

/* Variables and functions */

void
sbtoxsockbuf(struct sockbuf *sb, struct xsockbuf *xsb)
{

	xsb->sb_cc = sb->sb_ccc;
	xsb->sb_hiwat = sb->sb_hiwat;
	xsb->sb_mbcnt = sb->sb_mbcnt;
	xsb->sb_mcnt = sb->sb_mcnt;	
	xsb->sb_ccnt = sb->sb_ccnt;
	xsb->sb_mbmax = sb->sb_mbmax;
	xsb->sb_lowat = sb->sb_lowat;
	xsb->sb_flags = sb->sb_flags;
	xsb->sb_timeo = sb->sb_timeo;
}