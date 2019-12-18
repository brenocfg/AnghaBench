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
struct TYPE_2__ {int tv_sec; } ;
struct event_config {int limit_callbacks_after_prio; int /*<<< orphan*/  max_dispatch_callbacks; TYPE_1__ max_dispatch_interval; int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct event_config* mm_calloc (int,int) ; 

struct event_config *
event_config_new(void)
{
	struct event_config *cfg = mm_calloc(1, sizeof(*cfg));

	if (cfg == NULL)
		return (NULL);

	TAILQ_INIT(&cfg->entries);
	cfg->max_dispatch_interval.tv_sec = -1;
	cfg->max_dispatch_callbacks = INT_MAX;
	cfg->limit_callbacks_after_prio = 1;

	return (cfg);
}