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
struct TYPE_2__ {int /*<<< orphan*/  (* acu_disconnect ) () ;int /*<<< orphan*/  acu_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DV ; 
 int /*<<< orphan*/  HOST ; 
 char* NOSTR ; 
 int /*<<< orphan*/  VERBOSE ; 
 TYPE_1__* acu ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conflag ; 
 int /*<<< orphan*/  logent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

void
disconnect(char *reason)
{
	if (!conflag) {
		logent(value(HOST), "", DV, "call terminated");
		return;
	}
	if (reason == NOSTR) {
		logent(value(HOST), "", acu->acu_name, "call terminated");
		if (boolean(value(VERBOSE)))
			printf("\r\ndisconnecting...");
	} else
		logent(value(HOST), "", acu->acu_name, reason);
	(*acu->acu_disconnect)();
}