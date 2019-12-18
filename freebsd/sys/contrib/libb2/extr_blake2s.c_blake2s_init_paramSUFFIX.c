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
typedef  TYPE_1__ blake2s_state ;
struct TYPE_7__ {int /*<<< orphan*/  digest_length; } ;
typedef  TYPE_2__ blake2s_param ;

/* Variables and functions */
 int BLAKE2S_OUTBYTES ; 
 scalar_t__ blake2s_IV ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int blake2s_init_param( blake2s_state *S, const blake2s_param *P )
{
  uint8_t *p, *h, *v;
  //blake2s_init0( S );
  v = ( uint8_t * )( blake2s_IV );
  h = ( uint8_t * )( S->h );
  p = ( uint8_t * )( P );
  /* IV XOR ParamBlock */
  memset( S, 0, sizeof( blake2s_state ) );

  for( int i = 0; i < BLAKE2S_OUTBYTES; ++i ) h[i] = v[i] ^ p[i];

  S->outlen = P->digest_length;
  return 0;
}