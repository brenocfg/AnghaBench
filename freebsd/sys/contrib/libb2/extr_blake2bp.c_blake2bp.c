#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_6__ {int last_node; } ;
typedef  TYPE_1__ blake2b_state ;

/* Variables and functions */
 int BLAKE2B_BLOCKBYTES ; 
 size_t BLAKE2B_KEYBYTES ; 
 int BLAKE2B_OUTBYTES ; 
 int PARALLELISM_DEGREE ; 
 int blake2b_final (TYPE_1__*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  blake2b_update (TYPE_1__*,int /*<<< orphan*/  const*,size_t const) ; 
 scalar_t__ blake2bp_init_leaf (TYPE_1__*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,size_t) ; 
 scalar_t__ blake2bp_init_root (TYPE_1__*,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omp_get_thread_num () ; 
 int /*<<< orphan*/  omp_set_num_threads (int) ; 
 int /*<<< orphan*/  secure_zero_memory (int /*<<< orphan*/  const*,int) ; 

int blake2bp( uint8_t *out, const void *in, const void *key, size_t outlen, size_t inlen, size_t keylen )
{
  uint8_t hash[PARALLELISM_DEGREE][BLAKE2B_OUTBYTES];
  blake2b_state S[PARALLELISM_DEGREE][1];
  blake2b_state FS[1];

  /* Verify parameters */
  if ( NULL == in && inlen > 0 ) return -1;

  if ( NULL == out ) return -1;

  if ( NULL == key && keylen > 0) return -1;

  if( !outlen || outlen > BLAKE2B_OUTBYTES ) return -1;

  if( keylen > BLAKE2B_KEYBYTES ) return -1;

  for( size_t i = 0; i < PARALLELISM_DEGREE; ++i )
    if( blake2bp_init_leaf( S[i], ( uint8_t ) outlen, ( uint8_t ) keylen, i ) < 0 )
      return -1;

  S[PARALLELISM_DEGREE - 1]->last_node = 1; // mark last node

  if( keylen > 0 )
  {
    uint8_t block[BLAKE2B_BLOCKBYTES];
    memset( block, 0, BLAKE2B_BLOCKBYTES );
    memcpy( block, key, keylen );

    for( size_t i = 0; i < PARALLELISM_DEGREE; ++i )
      blake2b_update( S[i], block, BLAKE2B_BLOCKBYTES );

    secure_zero_memory( block, BLAKE2B_BLOCKBYTES ); /* Burn the key from stack */
  }

#if defined(_OPENMP)
  omp_set_num_threads(PARALLELISM_DEGREE);
  #pragma omp parallel shared(S,hash)
#else
  for( size_t id__ = 0; id__ < PARALLELISM_DEGREE; ++id__ )
#endif
  {
#if defined(_OPENMP)
    size_t      id__ = ( size_t ) omp_get_thread_num();
#endif
    size_t inlen__ = inlen;
    const uint8_t *in__ = ( const uint8_t * )in;
    in__ += id__ * BLAKE2B_BLOCKBYTES;

    while( inlen__ >= PARALLELISM_DEGREE * BLAKE2B_BLOCKBYTES )
    {
      blake2b_update( S[id__], in__, BLAKE2B_BLOCKBYTES );
      in__ += PARALLELISM_DEGREE * BLAKE2B_BLOCKBYTES;
      inlen__ -= PARALLELISM_DEGREE * BLAKE2B_BLOCKBYTES;
    }

    if( inlen__ > id__ * BLAKE2B_BLOCKBYTES )
    {
      const size_t left = inlen__ - id__ * BLAKE2B_BLOCKBYTES;
      const size_t len = left <= BLAKE2B_BLOCKBYTES ? left : BLAKE2B_BLOCKBYTES;
      blake2b_update( S[id__], in__, len );
    }

    blake2b_final( S[id__], hash[id__], BLAKE2B_OUTBYTES );
  }

  if( blake2bp_init_root( FS, ( uint8_t ) outlen, ( uint8_t ) keylen ) < 0 )
    return -1;

  FS->last_node = 1; // Mark as last node

  for( size_t i = 0; i < PARALLELISM_DEGREE; ++i )
    blake2b_update( FS, hash[i], BLAKE2B_OUTBYTES );

  return blake2b_final( FS, out, outlen );
}