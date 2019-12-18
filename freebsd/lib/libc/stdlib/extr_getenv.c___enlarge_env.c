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
struct envVars {int dummy; } ;

/* Variables and functions */
 struct envVars* envVars ; 
 int envVarsSize ; 
 int envVarsTotal ; 
 struct envVars* reallocarray (struct envVars*,int,int) ; 

__attribute__((used)) static inline bool
__enlarge_env(void)
{
	int newEnvVarsSize;
	struct envVars *tmpEnvVars;

	envVarsTotal++;
	if (envVarsTotal > envVarsSize) {
		newEnvVarsSize = envVarsTotal * 2;
		tmpEnvVars = reallocarray(envVars, newEnvVarsSize,
		    sizeof(*envVars));
		if (tmpEnvVars == NULL) {
			envVarsTotal--;
			return (false);
		}
		envVarsSize = newEnvVarsSize;
		envVars = tmpEnvVars;
	}

	return (true);
}