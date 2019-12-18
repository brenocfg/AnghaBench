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
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_CFG_TYPE_DEFAULT ; 
#define  MOD_LOAD 128 
 int /*<<< orphan*/  lio_init_device_list (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lio_event(struct module *mod, int event, void *junk)
{

	switch (event) {
	case MOD_LOAD:
		lio_init_device_list(LIO_CFG_TYPE_DEFAULT);
		break;
	default:
		break;
	}

	return (0);
}