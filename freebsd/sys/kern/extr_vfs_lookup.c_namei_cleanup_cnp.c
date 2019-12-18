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
struct componentname {int /*<<< orphan*/ * cn_nameptr; int /*<<< orphan*/ * cn_pnbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  namei_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
namei_cleanup_cnp(struct componentname *cnp)
{

	uma_zfree(namei_zone, cnp->cn_pnbuf);
#ifdef DIAGNOSTIC
	cnp->cn_pnbuf = NULL;
	cnp->cn_nameptr = NULL;
#endif
}