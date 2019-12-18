#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {size_t buflen; int /*<<< orphan*/  const* buf; } ;
typedef  TYPE_1__ blake2s_state ;

/* Variables and functions */
 int BLAKE2S_BLOCKBYTES ; 
 int /*<<< orphan*/  blake2s_compress (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  blake2s_increment_counter (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

int blake2s_update( blake2s_state *S, const uint8_t *in, size_t inlen )
{
  while( inlen > 0 )
  {
    size_t left = S->buflen;
    size_t fill = 2 * BLAKE2S_BLOCKBYTES - left;

    if( inlen > fill )
    {
      memcpy( S->buf + left, in, fill ); // Fill buffer
      S->buflen += fill;
      blake2s_increment_counter( S, BLAKE2S_BLOCKBYTES );
      blake2s_compress( S, S->buf ); // Compress
      memcpy( S->buf, S->buf + BLAKE2S_BLOCKBYTES, BLAKE2S_BLOCKBYTES ); // Shift buffer left
      S->buflen -= BLAKE2S_BLOCKBYTES;
      in += fill;
      inlen -= fill;
    }
    else /* inlen <= fill */
    {
      memcpy( S->buf + left, in, inlen );
      S->buflen += inlen; // Be lazy, do not compress
      in += inlen;
      inlen -= inlen;
    }
  }

  return 0;
}