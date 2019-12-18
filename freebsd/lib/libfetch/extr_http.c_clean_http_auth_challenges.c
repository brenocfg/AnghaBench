#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ ** challenges; } ;
typedef  TYPE_1__ http_auth_challenges_t ;

/* Variables and functions */
 int MAX_CHALLENGES ; 
 int /*<<< orphan*/  clean_http_auth_challenge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_http_auth_challenges (TYPE_1__*) ; 

__attribute__((used)) static void
clean_http_auth_challenges(http_auth_challenges_t *cs)
{
	int i;
	/* We rely on non-zero pointers being allocated, not on the count */
	for (i = 0; i < MAX_CHALLENGES; i++) {
		if (cs->challenges[i] != NULL) {
			clean_http_auth_challenge(cs->challenges[i]);
			free(cs->challenges[i]);
		}
	}
	init_http_auth_challenges(cs);
}