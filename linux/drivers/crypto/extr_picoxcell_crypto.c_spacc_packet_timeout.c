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
struct timer_list {int dummy; } ;
struct spacc_engine {int dummy; } ;

/* Variables and functions */
 struct spacc_engine* engine ; 
 struct spacc_engine* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_timeout ; 
 int /*<<< orphan*/  spacc_process_done (struct spacc_engine*) ; 

__attribute__((used)) static void spacc_packet_timeout(struct timer_list *t)
{
	struct spacc_engine *engine = from_timer(engine, t, packet_timeout);

	spacc_process_done(engine);
}