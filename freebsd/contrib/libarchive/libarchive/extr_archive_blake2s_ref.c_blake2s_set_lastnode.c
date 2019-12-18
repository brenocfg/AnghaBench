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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__* f; } ;
typedef  TYPE_1__ blake2s_state ;

/* Variables and functions */

__attribute__((used)) static void blake2s_set_lastnode( blake2s_state *S )
{
  S->f[1] = (uint32_t)-1;
}