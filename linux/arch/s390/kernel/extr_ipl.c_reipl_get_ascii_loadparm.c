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
struct TYPE_2__ {int /*<<< orphan*/  loadparm; } ;
struct ipl_parameter_block {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBCASC (char*,size_t) ; 
 size_t LOADPARM_LEN ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strim (char*) ; 

__attribute__((used)) static void reipl_get_ascii_loadparm(char *loadparm,
				     struct ipl_parameter_block *ibp)
{
	memcpy(loadparm, ibp->common.loadparm, LOADPARM_LEN);
	EBCASC(loadparm, LOADPARM_LEN);
	loadparm[LOADPARM_LEN] = 0;
	strim(loadparm);
}