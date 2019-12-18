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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  uni_fini () ; 
 int /*<<< orphan*/  uni_init () ; 

__attribute__((used)) static int
ng_uni_mod_event(module_t mod, int event, void *data)
{
	int error = 0;

	switch(event) {

	  case MOD_LOAD:
		uni_init();
		break;

	  case MOD_UNLOAD:
		uni_fini();
		break;

	  default:
		error = EOPNOTSUPP;
		break;
	}
	return (error);
}