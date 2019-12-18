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
typedef  int uint64_t ;
typedef  void* uint32_t ;
struct TYPE_3__ {int* t; } ;
typedef  TYPE_1__ blake2s_state ;

/* Variables and functions */

__attribute__((used)) static inline int blake2s_increment_counter( blake2s_state *S, const uint32_t inc )
{
  uint64_t t = ( ( uint64_t )S->t[1] << 32 ) | S->t[0];
  t += inc;
  S->t[0] = ( uint32_t )( t >>  0 );
  S->t[1] = ( uint32_t )( t >> 32 );
  return 0;
}