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
 struct event_base* check_dummy_mem_ok (struct event_base*) ; 
 int /*<<< orphan*/  dummy_free ; 
 int /*<<< orphan*/  dummy_malloc ; 
 int /*<<< orphan*/  dummy_realloc ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_base_new_with_config (struct event_config*) ; 
 int /*<<< orphan*/  event_config_avoid_method (struct event_config*,char*) ; 
 int /*<<< orphan*/  event_config_free (struct event_config*) ; 
 struct event_config* event_config_new () ; 
 int /*<<< orphan*/  event_set_mem_functions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tt_assert (struct event_base*) ; 

__attribute__((used)) static void
test_mm_functions(void *arg)
{
	struct event_base *b = NULL;
	struct event_config *cfg = NULL;
	event_set_mem_functions(dummy_malloc, dummy_realloc, dummy_free);
	cfg = event_config_new();
	event_config_avoid_method(cfg, "Nonesuch");
	b = event_base_new_with_config(cfg);
	tt_assert(b);
	tt_assert(check_dummy_mem_ok(b));
end:
	if (cfg)
		event_config_free(cfg);
	if (b)
		event_base_free(b);
}