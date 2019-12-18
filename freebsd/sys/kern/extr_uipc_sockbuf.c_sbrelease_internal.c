#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_1__* so_cred; } ;
struct sockbuf {scalar_t__ sb_mbmax; int /*<<< orphan*/  sb_hiwat; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr_uidinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  chgsbsize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbflush_internal (struct sockbuf*) ; 

void
sbrelease_internal(struct sockbuf *sb, struct socket *so)
{

	sbflush_internal(sb);
	(void)chgsbsize(so->so_cred->cr_uidinfo, &sb->sb_hiwat, 0,
	    RLIM_INFINITY);
	sb->sb_mbmax = 0;
}