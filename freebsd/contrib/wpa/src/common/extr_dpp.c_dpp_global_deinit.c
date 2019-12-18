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
struct dpp_global {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpp_global_clear (struct dpp_global*) ; 
 int /*<<< orphan*/  os_free (struct dpp_global*) ; 

void dpp_global_deinit(struct dpp_global *dpp)
{
	dpp_global_clear(dpp);
	os_free(dpp);
}