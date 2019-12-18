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
typedef  int uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  outlen; scalar_t__ h; } ;
typedef  TYPE_1__ blake2b_state ;
struct TYPE_7__ {int /*<<< orphan*/  digest_length; } ;
typedef  TYPE_2__ blake2b_param ;

/* Variables and functions */
 int BLAKE2B_OUTBYTES ; 
 scalar_t__ blake2b_IV ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int blake2b_init_param( blake2b_state *S, const blake2b_param *P )
{
  uint8_t *p, *h, *v;
  //blake2b_init0( S );
  v = ( uint8_t * )( blake2b_IV );
  h = ( uint8_t * )( S->h );
  p = ( uint8_t * )( P );
  /* IV XOR ParamBlock */
  memset( S, 0, sizeof( blake2b_state ) );

  for( int i = 0; i < BLAKE2B_OUTBYTES; ++i ) h[i] = v[i] ^ p[i];

  S->outlen = P->digest_length;
  return 0;
}