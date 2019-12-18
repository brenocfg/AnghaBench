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
struct evutil_monotonic_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct evutil_monotonic_timer*,int /*<<< orphan*/ ,int) ; 
 struct evutil_monotonic_timer* mm_malloc (int) ; 

struct evutil_monotonic_timer *
evutil_monotonic_timer_new(void)
{
  struct evutil_monotonic_timer *p = NULL;

  p = mm_malloc(sizeof(*p));
  if (!p) goto done;

  memset(p, 0, sizeof(*p));

 done:
  return p;
}