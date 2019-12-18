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
struct TYPE_3__ {char* au_name; } ;
typedef  TYPE_1__ au_user_ent_t ;

/* Variables and functions */
 TYPE_1__* getauuserent () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
audump_user(void)
{
	au_user_ent_t *up;

	while ((up = getauuserent()) != NULL) {
		printf("%s:", up->au_name);
		// printf_classmask(up->au_always);
		printf(":");
		// printf_classmask(up->au_never);
		printf("\n");
	}
}