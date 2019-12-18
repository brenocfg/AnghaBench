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
struct TYPE_4__ {int loaded; int /*<<< orphan*/  numareas; } ;
struct TYPE_3__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_AllocMaxAAS () ; 
 int /*<<< orphan*/  AAS_StoreBoundingBoxes () ; 
 int /*<<< orphan*/  AAS_StoreTree_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Log_Write (char*,...) ; 
 TYPE_2__ aasworld ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 TYPE_1__ tmpaasworld ; 

void AAS_StoreFile(char *filename)
{
	AAS_AllocMaxAAS();

	Log_Write("AAS_StoreFile\r\n");
	//
	AAS_StoreBoundingBoxes();
	//
	qprintf("%6d areas stored", 0);
	//start with node 1 because node zero is a dummy
	AAS_StoreTree_r(tmpaasworld.nodes);
	qprintf("\n");
	Log_Write("%6d areas stored\r\n", aasworld.numareas);
	aasworld.loaded = true;
}