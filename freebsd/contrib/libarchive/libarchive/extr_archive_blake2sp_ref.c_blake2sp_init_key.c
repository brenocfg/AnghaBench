#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {size_t outlen; TYPE_3__** S; TYPE_2__* R; scalar_t__ buflen; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ blake2sp_state ;
struct TYPE_8__ {int last_node; } ;
struct TYPE_7__ {int last_node; } ;

/* Variables and functions */
 int BLAKE2S_BLOCKBYTES ; 
 size_t BLAKE2S_KEYBYTES ; 
 size_t BLAKE2S_OUTBYTES ; 
 size_t PARALLELISM_DEGREE ; 
 int /*<<< orphan*/  blake2s_update (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ blake2sp_init_leaf (TYPE_3__*,size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ blake2sp_init_root (TYPE_2__*,size_t,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  secure_zero_memory (int /*<<< orphan*/ *,int) ; 

int blake2sp_init_key( blake2sp_state *S, size_t outlen, const void *key, size_t keylen )
{
  size_t i;

  if( !outlen || outlen > BLAKE2S_OUTBYTES ) return -1;

  if( !key || !keylen || keylen > BLAKE2S_KEYBYTES ) return -1;

  memset( S->buf, 0, sizeof( S->buf ) );
  S->buflen = 0;
  S->outlen = outlen;

  if( blake2sp_init_root( S->R, outlen, keylen ) < 0 )
    return -1;

  for( i = 0; i < PARALLELISM_DEGREE; ++i )
    if( blake2sp_init_leaf( S->S[i], outlen, keylen, (uint32_t)i ) < 0 ) return -1;

  S->R->last_node = 1;
  S->S[PARALLELISM_DEGREE - 1]->last_node = 1;
  {
    uint8_t block[BLAKE2S_BLOCKBYTES];
    memset( block, 0, BLAKE2S_BLOCKBYTES );
    memcpy( block, key, keylen );

    for( i = 0; i < PARALLELISM_DEGREE; ++i )
      blake2s_update( S->S[i], block, BLAKE2S_BLOCKBYTES );

    secure_zero_memory( block, BLAKE2S_BLOCKBYTES ); /* Burn the key from stack */
  }
  return 0;
}