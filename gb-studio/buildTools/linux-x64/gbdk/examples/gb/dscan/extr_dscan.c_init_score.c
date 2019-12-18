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
 scalar_t__ pl ; 
 scalar_t__ pp ; 
 scalar_t__ ps ; 
 int /*<<< orphan*/  show_level (scalar_t__) ; 
 int /*<<< orphan*/  show_score (scalar_t__) ; 

void init_score()
{
  ps = 0;
  show_score( ps );
  pp = 0; pl = 0;
  show_level( pl );
}