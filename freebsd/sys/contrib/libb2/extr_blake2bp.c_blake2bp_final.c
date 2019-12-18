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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t outlen; size_t buflen; int /*<<< orphan*/  R; int /*<<< orphan*/ * S; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ blake2bp_state ;

/* Variables and functions */
 size_t BLAKE2B_BLOCKBYTES ; 
 int BLAKE2B_OUTBYTES ; 
 int PARALLELISM_DEGREE ; 
 int blake2b_final (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  blake2b_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int blake2bp_final( blake2bp_state *S, uint8_t *out, size_t outlen )
{
  uint8_t hash[PARALLELISM_DEGREE][BLAKE2B_OUTBYTES];

  if(S->outlen != outlen) return -1;

  for( size_t i = 0; i < PARALLELISM_DEGREE; ++i )
  {
    if( S->buflen > i * BLAKE2B_BLOCKBYTES )
    {
      size_t left = S->buflen - i * BLAKE2B_BLOCKBYTES;

      if( left > BLAKE2B_BLOCKBYTES ) left = BLAKE2B_BLOCKBYTES;

      blake2b_update( S->S[i], S->buf + i * BLAKE2B_BLOCKBYTES, left );
    }

    blake2b_final( S->S[i], hash[i], BLAKE2B_OUTBYTES );
  }

  for( size_t i = 0; i < PARALLELISM_DEGREE; ++i )
    blake2b_update( S->R, hash[i], BLAKE2B_OUTBYTES );

  return blake2b_final( S->R, out, outlen );
}