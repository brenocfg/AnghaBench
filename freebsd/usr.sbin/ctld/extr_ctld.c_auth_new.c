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
struct auth_group {int /*<<< orphan*/  ag_auths; } ;
struct auth {struct auth_group* a_auth_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct auth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_next ; 
 struct auth* calloc (int,int) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 

__attribute__((used)) static struct auth *
auth_new(struct auth_group *ag)
{
	struct auth *auth;

	auth = calloc(1, sizeof(*auth));
	if (auth == NULL)
		log_err(1, "calloc");
	auth->a_auth_group = ag;
	TAILQ_INSERT_TAIL(&ag->ag_auths, auth, a_next);
	return (auth);
}