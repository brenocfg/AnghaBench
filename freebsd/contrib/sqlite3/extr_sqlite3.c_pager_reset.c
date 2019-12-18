#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pPCache; int /*<<< orphan*/  pBackup; int /*<<< orphan*/  iDataVersion; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3BackupRestart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3PcacheClear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pager_reset(Pager *pPager){
  pPager->iDataVersion++;
  sqlite3BackupRestart(pPager->pBackup);
  sqlite3PcacheClear(pPager->pPCache);
}