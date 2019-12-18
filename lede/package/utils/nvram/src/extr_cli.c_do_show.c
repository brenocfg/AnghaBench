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
struct TYPE_3__ {char* name; char* value; struct TYPE_3__* next; } ;
typedef  TYPE_1__ nvram_tuple_t ;
typedef  int /*<<< orphan*/  nvram_handle_t ;

/* Variables and functions */
 TYPE_1__* nvram_getall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static int do_show(nvram_handle_t *nvram)
{
	nvram_tuple_t *t;
	int stat = 1;

	if( (t = nvram_getall(nvram)) != NULL )
	{
		while( t )
		{
			printf("%s=%s\n", t->name, t->value);
			t = t->next;
		}

		stat = 0;
	}

	return stat;
}