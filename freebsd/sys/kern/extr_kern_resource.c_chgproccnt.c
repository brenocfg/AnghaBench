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
struct uidinfo {int /*<<< orphan*/  ui_proccnt; } ;
typedef  int /*<<< orphan*/  rlim_t ;

/* Variables and functions */
 int chglimit (struct uidinfo*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 

int
chgproccnt(struct uidinfo *uip, int diff, rlim_t max)
{

	return (chglimit(uip, &uip->ui_proccnt, diff, max, "proccnt"));
}