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
typedef  int /*<<< orphan*/  GColors ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_DEFAULT ; 
 int /*<<< orphan*/ * get_color (int /*<<< orphan*/ ) ; 

GColors *
color_default (void)
{
  return get_color (COLOR_DEFAULT);
}