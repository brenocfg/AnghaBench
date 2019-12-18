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
struct omap_sr {int dummy; } ;

/* Variables and functions */
 int sr_configure_errgen (struct omap_sr*) ; 

__attribute__((used)) static int sr_class3_configure(struct omap_sr *sr)
{
	return sr_configure_errgen(sr);
}