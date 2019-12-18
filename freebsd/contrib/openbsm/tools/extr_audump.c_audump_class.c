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
struct TYPE_3__ {int ac_class; char* ac_name; char* ac_desc; } ;
typedef  TYPE_1__ au_class_ent_t ;

/* Variables and functions */
 TYPE_1__* getauclassent () ; 
 int /*<<< orphan*/  printf (char*,int,char*,char*) ; 

__attribute__((used)) static void
audump_class(void)
{
	au_class_ent_t *cp;

	while ((cp = getauclassent()) != NULL)
		printf("0x%08x:%s:%s\n", cp->ac_class, cp->ac_name,
		    cp->ac_desc);
}