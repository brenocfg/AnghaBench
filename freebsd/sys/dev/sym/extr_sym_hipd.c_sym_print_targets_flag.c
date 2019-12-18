#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hcb_p ;
struct TYPE_6__ {int myaddr; TYPE_1__* target; } ;
struct TYPE_5__ {int usrflags; } ;

/* Variables and functions */
 int SYM_CONF_MAX_TARGET ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* sym_name (TYPE_2__*) ; 

__attribute__((used)) static void sym_print_targets_flag(hcb_p np, int mask, char *msg)
{
	int cnt;
	int i;

	for (cnt = 0, i = 0 ; i < SYM_CONF_MAX_TARGET ; i++) {
		if (i == np->myaddr)
			continue;
		if (np->target[i].usrflags & mask) {
			if (!cnt++)
				printf("%s: %s disabled for targets",
					sym_name(np), msg);
			printf(" %d", i);
		}
	}
	if (cnt)
		printf(".\n");
}