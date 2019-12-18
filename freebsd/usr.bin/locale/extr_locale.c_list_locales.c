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
struct TYPE_2__ {size_t sl_cur; char** sl_str; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_locales_list () ; 
 TYPE_1__* locales ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void
list_locales(void)
{
	size_t i;

	init_locales_list();
	for (i = 0; i < locales->sl_cur; i++) {
		printf("%s\n", locales->sl_str[i]);
	}
}