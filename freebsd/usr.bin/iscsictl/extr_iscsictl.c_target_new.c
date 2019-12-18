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
struct target {struct conf* t_conf; } ;
struct conf {int /*<<< orphan*/  conf_targets; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct target*,int /*<<< orphan*/ ) ; 
 struct target* calloc (int,int) ; 
 int /*<<< orphan*/  t_next ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 

struct target *
target_new(struct conf *conf)
{
	struct target *targ;

	targ = calloc(1, sizeof(*targ));
	if (targ == NULL)
		xo_err(1, "calloc");
	targ->t_conf = conf;
	TAILQ_INSERT_TAIL(&conf->conf_targets, targ, t_next);

	return (targ);
}