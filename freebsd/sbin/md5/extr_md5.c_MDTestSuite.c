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
struct TYPE_3__ {char* name; int /*<<< orphan*/ ** TestOutput; int /*<<< orphan*/  (* Data ) (char*,int /*<<< orphan*/ ,char*) ;} ;
typedef  TYPE_1__ Algorithm_t ;

/* Variables and functions */
 int HEX_DIGEST_LENGTH ; 
 int MDTESTCOUNT ; 
 char** MDTestInput ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
MDTestSuite(const Algorithm_t *alg)
{
	int i;
	char buffer[HEX_DIGEST_LENGTH];

	printf("%s test suite:\n", alg->name);
	for (i = 0; i < MDTESTCOUNT; i++) {
		(*alg->Data)(MDTestInput[i], strlen(MDTestInput[i]), buffer);
		printf("%s (\"%s\") = %s", alg->name, MDTestInput[i], buffer);
		if (strcmp(buffer, (*alg->TestOutput)[i]) == 0)
			printf(" - verified correct\n");
		else
			printf(" - INCORRECT RESULT!\n");
	}
}