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
typedef  struct auth_name {int /*<<< orphan*/  an_initator_name; struct auth_group* an_auth_group; } const auth_name ;
struct auth_group {int /*<<< orphan*/  ag_names; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct auth_name const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  an_next ; 
 struct auth_name const* calloc (int,int) ; 
 int /*<<< orphan*/  checked_strdup (char const*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 

const struct auth_name *
auth_name_new(struct auth_group *ag, const char *name)
{
	struct auth_name *an;

	an = calloc(1, sizeof(*an));
	if (an == NULL)
		log_err(1, "calloc");
	an->an_auth_group = ag;
	an->an_initator_name = checked_strdup(name);
	TAILQ_INSERT_TAIL(&ag->ag_names, an, an_next);
	return (an);
}