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
struct bridge_if {int dummy; } ;

/* Variables and functions */
 struct bridge_if* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bridge_ifs ; 

struct bridge_if *
bridge_first_bif(void)
{
	return (TAILQ_FIRST(&bridge_ifs));
}