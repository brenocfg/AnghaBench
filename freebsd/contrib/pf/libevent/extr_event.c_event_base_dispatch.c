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
struct event_base {int dummy; } ;

/* Variables and functions */
 int event_base_loop (struct event_base*,int /*<<< orphan*/ ) ; 

int
event_base_dispatch(struct event_base *event_base)
{
  return (event_base_loop(event_base, 0));
}