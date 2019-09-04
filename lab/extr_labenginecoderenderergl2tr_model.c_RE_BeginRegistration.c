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
typedef  int /*<<< orphan*/  glconfig_t ;
struct TYPE_2__ {int* visClusters; int /*<<< orphan*/  registered; scalar_t__ visIndex; } ;

/* Variables and functions */
 int MAX_VISCOUNTS ; 
 int /*<<< orphan*/  RE_ClearScene () ; 
 int /*<<< orphan*/  R_ClearFlares () ; 
 int /*<<< orphan*/  R_Init () ; 
 int /*<<< orphan*/  R_IssuePendingRenderCommands () ; 
 int /*<<< orphan*/  glConfig ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__ tr ; 

void RE_BeginRegistration( glconfig_t *glconfigOut ) {
	int	i;

	R_Init();

	*glconfigOut = glConfig;

	R_IssuePendingRenderCommands();

	tr.visIndex = 0;
	// force markleafs to regenerate
	for(i = 0; i < MAX_VISCOUNTS; i++) {
		tr.visClusters[i] = -2;
	}

	R_ClearFlares();
	RE_ClearScene();

	tr.registered = qtrue;
}