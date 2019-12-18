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
struct interface_info {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/ * alias; int /*<<< orphan*/ * active; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_INIT ; 
 int /*<<< orphan*/  script_go () ; 
 int /*<<< orphan*/  script_init (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  script_write_params (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
disassoc(void *arg)
{
	struct interface_info *_ifi = arg;

	/*
	 * Clear existing state.
	 */
	if (_ifi->client->active != NULL) {
		script_init("EXPIRE", NULL);
		script_write_params("old_",
		    _ifi->client->active);
		if (_ifi->client->alias)
			script_write_params("alias_",
				_ifi->client->alias);
		script_go();
	}
	_ifi->client->state = S_INIT;
}