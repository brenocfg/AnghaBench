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
struct event_config {int dummy; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 struct event_base* event_base_new_with_config (struct event_config*) ; 
 int /*<<< orphan*/  event_config_free (struct event_config*) ; 
 struct event_config* event_config_new () ; 

struct event_base *
event_base_new(void)
{
	struct event_base *base = NULL;
	struct event_config *cfg = event_config_new();
	if (cfg) {
		base = event_base_new_with_config(cfg);
		event_config_free(cfg);
	}
	return base;
}