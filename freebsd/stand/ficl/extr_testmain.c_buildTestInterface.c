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
typedef  int /*<<< orphan*/  FICL_SYSTEM ;

/* Variables and functions */
 int /*<<< orphan*/  FW_DEFAULT ; 
 int /*<<< orphan*/  clocksPerSec ; 
 int /*<<< orphan*/  execxt ; 
 int /*<<< orphan*/  ficlBreak ; 
 int /*<<< orphan*/  ficlBuild (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ficlChDir ; 
 int /*<<< orphan*/  ficlClock ; 
 int /*<<< orphan*/  ficlGetCWD ; 
 int /*<<< orphan*/  ficlLoad ; 
 int /*<<< orphan*/  ficlSystem ; 
 int /*<<< orphan*/  spewHash ; 

void buildTestInterface(FICL_SYSTEM *pSys)
{
    ficlBuild(pSys, "break",    ficlBreak,    FW_DEFAULT);
    ficlBuild(pSys, "clock",    ficlClock,    FW_DEFAULT);
    ficlBuild(pSys, "cd",       ficlChDir,    FW_DEFAULT);
    ficlBuild(pSys, "execxt",   execxt,       FW_DEFAULT);
    ficlBuild(pSys, "load",     ficlLoad,     FW_DEFAULT);
    ficlBuild(pSys, "pwd",      ficlGetCWD,   FW_DEFAULT);
    ficlBuild(pSys, "system",   ficlSystem,   FW_DEFAULT);
    ficlBuild(pSys, "spewhash", spewHash,     FW_DEFAULT);
    ficlBuild(pSys, "clocks/sec", 
                                clocksPerSec, FW_DEFAULT);

    return;
}