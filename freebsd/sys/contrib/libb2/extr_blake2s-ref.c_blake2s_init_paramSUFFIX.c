#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  outlen; int /*<<< orphan*/ * h; } ;
typedef  TYPE_1__ blake2s_state ;
struct TYPE_7__ {int /*<<< orphan*/  digest_length; } ;
typedef  TYPE_2__ blake2s_param ;

/* Variables and functions */
 int /*<<< orphan*/  blake2s_init0 (TYPE_1__*) ; 
 int /*<<< orphan*/  load32 (int /*<<< orphan*/ *) ; 

int blake2s_init_param( blake2s_state *S, const blake2s_param *P )
{
  blake2s_init0( S );
  uint32_t *p = ( uint32_t * )( P );

  /* IV XOR ParamBlock */
  for( size_t i = 0; i < 8; ++i )
    S->h[i] ^= load32( &p[i] );

  S->outlen = P->digest_length;
  return 0;
}