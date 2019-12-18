#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  bp; int /*<<< orphan*/  len; } ;
struct TYPE_9__ {TYPE_3__** argv; } ;
struct TYPE_8__ {int /*<<< orphan*/  gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ EXCMD ;
typedef  TYPE_3__ ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  F_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_ABBREV ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  SEQ_ABBREV ; 
 int /*<<< orphan*/  msgq_wstr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ seq_delete (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ex_unabbr(SCR *sp, EXCMD *cmdp)
{
	ARGS *ap;

	ap = cmdp->argv[0];
	if (!F_ISSET(sp->gp, G_ABBREV) ||
	    seq_delete(sp, ap->bp, ap->len, SEQ_ABBREV)) {
		msgq_wstr(sp, M_ERR, ap->bp,
		    "109|\"%s\" is not an abbreviation");
		return (1);
	}
	return (0);
}