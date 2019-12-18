#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {size_t outlen; TYPE_3__** S; TYPE_2__* R; scalar_t__ buflen; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ blake2sp_state ;
struct TYPE_7__ {int last_node; } ;
struct TYPE_6__ {int last_node; } ;

/* Variables and functions */
 size_t BLAKE2S_OUTBYTES ; 
 size_t PARALLELISM_DEGREE ; 
 scalar_t__ blake2sp_init_leaf (TYPE_3__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ blake2sp_init_root (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int blake2sp_init( blake2sp_state *S, size_t outlen )
{
  size_t i;

  if( !outlen || outlen > BLAKE2S_OUTBYTES ) return -1;

  memset( S->buf, 0, sizeof( S->buf ) );
  S->buflen = 0;
  S->outlen = outlen;

  if( blake2sp_init_root( S->R, outlen, 0 ) < 0 )
    return -1;

  for( i = 0; i < PARALLELISM_DEGREE; ++i )
    if( blake2sp_init_leaf( S->S[i], outlen, 0, (uint32_t)i ) < 0 ) return -1;

  S->R->last_node = 1;
  S->S[PARALLELISM_DEGREE - 1]->last_node = 1;
  return 0;
}