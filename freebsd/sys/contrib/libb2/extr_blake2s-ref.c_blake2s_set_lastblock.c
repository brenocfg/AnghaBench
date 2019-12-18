#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int* f; scalar_t__ last_node; } ;
typedef  TYPE_1__ blake2s_state ;

/* Variables and functions */
 int /*<<< orphan*/  blake2s_set_lastnode (TYPE_1__*) ; 

__attribute__((used)) static inline int blake2s_set_lastblock( blake2s_state *S )
{
  if( S->last_node ) blake2s_set_lastnode( S );

  S->f[0] = ~0U;
  return 0;
}