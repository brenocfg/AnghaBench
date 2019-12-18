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
struct TYPE_2__ {char* dv_name; } ;

/* Variables and functions */
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int pager_output (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/ * pxe_call ; 
 TYPE_1__ pxedisk ; 
 int /*<<< orphan*/  rootip ; 
 char* rootpath ; 

__attribute__((used)) static int
pxe_print(int verbose)
{
	if (pxe_call == NULL)
		return (0);

	printf("%s devices:", pxedisk.dv_name);
	if (pager_output("\n") != 0)
		return (1);
	printf("    %s0:", pxedisk.dv_name);
	if (verbose) {
		printf("    %s:%s", inet_ntoa(rootip), rootpath);
	}
	return (pager_output("\n"));
}