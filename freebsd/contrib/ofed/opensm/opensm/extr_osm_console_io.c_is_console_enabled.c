#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  console; } ;
typedef  TYPE_1__ osm_subn_opt_t ;

/* Variables and functions */
 scalar_t__ is_local (int /*<<< orphan*/ ) ; 
 scalar_t__ is_loopback (int /*<<< orphan*/ ) ; 
 scalar_t__ is_remote (int /*<<< orphan*/ ) ; 

int is_console_enabled(osm_subn_opt_t * p_opt)
{
	/* checks for a variety of types of consoles - default is off or 0 */
	if (p_opt)
		return is_local(p_opt->console) || is_loopback(p_opt->console)
			|| is_remote(p_opt->console);
	return 0;
}