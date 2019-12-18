#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  recno_t ;
struct TYPE_8__ {int /*<<< orphan*/  ep; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  F_FIRSTMODIFY ; 
 scalar_t__ F_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_RCV_ON ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  NEEDFILE (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCV_SNAPSHOT ; 
 scalar_t__ db_last (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rcv_init (TYPE_1__*) ; 
 scalar_t__ rcv_sync (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
ex_preserve(SCR *sp, EXCMD *cmdp)
{
	recno_t lno;

	NEEDFILE(sp, cmdp);

	if (!F_ISSET(sp->ep, F_RCV_ON)) {
		msgq(sp, M_ERR, "142|Preservation of this file not possible");
		return (1);
	}

	/* If recovery not initialized, do so. */
	if (F_ISSET(sp->ep, F_FIRSTMODIFY) && rcv_init(sp))
		return (1);

	/* Force the file to be read in, in case it hasn't yet. */
	if (db_last(sp, &lno))
		return (1);

	/* Sync to disk. */
	if (rcv_sync(sp, RCV_SNAPSHOT))
		return (1);

	msgq(sp, M_INFO, "143|File preserved");
	return (0);
}