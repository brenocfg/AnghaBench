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
struct conf {int /*<<< orphan*/  conf_targets; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct conf* calloc (int,int) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 

struct conf *
conf_new(void)
{
	struct conf *conf;

	conf = calloc(1, sizeof(*conf));
	if (conf == NULL)
		xo_err(1, "calloc");

	TAILQ_INIT(&conf->conf_targets);

	return (conf);
}