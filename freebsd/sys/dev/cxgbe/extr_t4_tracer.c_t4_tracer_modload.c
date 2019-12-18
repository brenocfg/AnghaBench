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

/* Variables and functions */
 int /*<<< orphan*/  if_clone_advanced (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  t4_cloner ; 
 int /*<<< orphan*/  t4_cloner_create ; 
 int /*<<< orphan*/  t4_cloner_destroy ; 
 int /*<<< orphan*/  t4_cloner_match ; 
 int /*<<< orphan*/  t4_cloner_name ; 
 int /*<<< orphan*/  t4_trace_lock ; 

void
t4_tracer_modload()
{

	sx_init(&t4_trace_lock, "T4/T5 tracer lock");
	t4_cloner = if_clone_advanced(t4_cloner_name, 0, t4_cloner_match,
	    t4_cloner_create, t4_cloner_destroy);
}