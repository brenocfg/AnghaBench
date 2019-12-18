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
typedef  enum config_scope { ____Placeholder_config_scope } config_scope ;
struct TYPE_2__ {int scope; } ;

/* Variables and functions */
 TYPE_1__* current_config_kvi ; 
 int current_parsing_scope ; 

enum config_scope current_config_scope(void)
{
	if (current_config_kvi)
		return current_config_kvi->scope;
	else
		return current_parsing_scope;
}