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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  CFE_ENV_SIZE ; 
 int KENV_MNAMELEN ; 
 int KENV_MVALLEN ; 
 scalar_t__ cfe_enumenv (int,char*,int,char*,int) ; 
 int /*<<< orphan*/  cfe_env_buf ; 
 int /*<<< orphan*/  init_static_kenv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kern_setenv (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

void
cfe_env_init(void)
{
	int idx;
	char name[KENV_MNAMELEN], val[KENV_MVALLEN];

	init_static_kenv(cfe_env_buf, CFE_ENV_SIZE);

	idx = 0;
	while (1) {
		if (cfe_enumenv(idx, name, sizeof(name), val, sizeof(val)) != 0)
			break;

		if (kern_setenv(name, val) != 0) {
			printf("No space to store CFE env: \"%s=%s\"\n",
				name, val);
		}
		++idx;
	}
}