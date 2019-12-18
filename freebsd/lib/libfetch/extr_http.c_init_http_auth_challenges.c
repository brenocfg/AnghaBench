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
struct TYPE_3__ {scalar_t__ valid; scalar_t__ count; int /*<<< orphan*/ ** challenges; } ;
typedef  TYPE_1__ http_auth_challenges_t ;

/* Variables and functions */
 int MAX_CHALLENGES ; 

__attribute__((used)) static void
init_http_auth_challenges(http_auth_challenges_t *cs)
{
	int i;
	for (i = 0; i < MAX_CHALLENGES; i++)
		cs->challenges[i] = NULL;
	cs->count = cs->valid = 0;
}