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
struct sppp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lcp ; 
 int /*<<< orphan*/  sppp_to_event (int /*<<< orphan*/ *,struct sppp*) ; 

__attribute__((used)) static void
sppp_lcp_TO(void *cookie)
{
	sppp_to_event(&lcp, (struct sppp *)cookie);
}