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
struct TYPE_2__ {int /*<<< orphan*/  BSPModelMinsMaxsOrigin; int /*<<< orphan*/  Print; int /*<<< orphan*/  PointContents; int /*<<< orphan*/  Trace; int /*<<< orphan*/  FreeMemory; int /*<<< orphan*/  GetMemory; int /*<<< orphan*/  BSPEntityData; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotImport_BSPEntityData ; 
 int /*<<< orphan*/  BotImport_BSPModelMinsMaxsOrigin ; 
 int /*<<< orphan*/  BotImport_GetMemory ; 
 int /*<<< orphan*/  BotImport_PointContents ; 
 int /*<<< orphan*/  BotImport_Print ; 
 int /*<<< orphan*/  BotImport_Trace ; 
 int /*<<< orphan*/  FreeMemory ; 
 TYPE_1__ botimport ; 

void AAS_InitBotImport(void)
{
	botimport.BSPEntityData = BotImport_BSPEntityData;
	botimport.GetMemory = BotImport_GetMemory;
	botimport.FreeMemory = FreeMemory;
	botimport.Trace = BotImport_Trace;
	botimport.PointContents = BotImport_PointContents;
	botimport.Print = BotImport_Print;
	botimport.BSPModelMinsMaxsOrigin = BotImport_BSPModelMinsMaxsOrigin;
}