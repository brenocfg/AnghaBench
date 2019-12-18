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
struct state {scalar_t__ s; scalar_t__ theend; } ;

/* Variables and functions */

__attribute__((used)) static int
sn_reserve (struct state *state, size_t n)
{
  return state->s + n > state->theend;
}