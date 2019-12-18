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
struct sockbuf {int sb_flags; int /*<<< orphan*/  sb_timeo; int /*<<< orphan*/  sb_mtx; int /*<<< orphan*/  sb_acc; } ;

/* Variables and functions */
 int PCATCH ; 
 int PSOCK ; 
 int SB_NOINTR ; 
 int SB_WAIT ; 
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (struct sockbuf*) ; 
 int msleep_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sbwait(struct sockbuf *sb)
{

	SOCKBUF_LOCK_ASSERT(sb);

	sb->sb_flags |= SB_WAIT;
	return (msleep_sbt(&sb->sb_acc, &sb->sb_mtx,
	    (sb->sb_flags & SB_NOINTR) ? PSOCK : PSOCK | PCATCH, "sbwait",
	    sb->sb_timeo, 0, 0));
}