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
struct TYPE_2__ {char* name; scalar_t__ active; } ;

/* Variables and functions */
 int envActive ; 
 TYPE_1__* envVars ; 
 int envVarsTotal ; 
 char** environ ; 
 int environSize ; 
 char** intEnviron ; 
 char** reallocarray (char**,int,int) ; 

__attribute__((used)) static int
__rebuild_environ(int newEnvironSize)
{
	char **tmpEnviron;
	int envNdx;
	int environNdx;
	int tmpEnvironSize;

	/* Resize environ. */
	if (newEnvironSize > environSize) {
		tmpEnvironSize = newEnvironSize * 2;
		tmpEnviron = reallocarray(intEnviron, tmpEnvironSize + 1,
		    sizeof(*intEnviron));
		if (tmpEnviron == NULL)
			return (-1);
		environSize = tmpEnvironSize;
		intEnviron = tmpEnviron;
	}
	envActive = newEnvironSize;

	/* Assign active variables to environ. */
	for (envNdx = envVarsTotal - 1, environNdx = 0; envNdx >= 0; envNdx--)
		if (envVars[envNdx].active)
			intEnviron[environNdx++] = envVars[envNdx].name;
	intEnviron[environNdx] = NULL;

	/* Always set environ which may have been replaced by program. */
	environ = intEnviron;

	return (0);
}