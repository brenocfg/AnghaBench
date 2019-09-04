#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nr; TYPE_1__* items; } ;
struct credential {scalar_t__ password; scalar_t__ username; TYPE_2__ helpers; scalar_t__ quit; } ;
struct TYPE_3__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  credential_apply_config (struct credential*) ; 
 int /*<<< orphan*/  credential_do (struct credential*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  credential_getpass (struct credential*) ; 
 int /*<<< orphan*/  die (char*,...) ; 

void credential_fill(struct credential *c)
{
	int i;

	if (c->username && c->password)
		return;

	credential_apply_config(c);

	for (i = 0; i < c->helpers.nr; i++) {
		credential_do(c, c->helpers.items[i].string, "get");
		if (c->username && c->password)
			return;
		if (c->quit)
			die("credential helper '%s' told us to quit",
			    c->helpers.items[i].string);
	}

	credential_getpass(c);
	if (!c->username && !c->password)
		die("unable to get password from user");
}