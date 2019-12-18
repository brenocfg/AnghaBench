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
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {scalar_t__ outlen; TYPE_3__** S; TYPE_2__* R; scalar_t__ buflen; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ blake2bp_state ;
struct TYPE_7__ {int last_node; } ;
struct TYPE_6__ {int last_node; } ;

/* Variables and functions */
 size_t BLAKE2B_OUTBYTES ; 
 size_t PARALLELISM_DEGREE ; 
 scalar_t__ blake2bp_init_leaf (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ blake2bp_init_root (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int blake2bp_init( blake2bp_state *S, size_t outlen )
{
  if( !outlen || outlen > BLAKE2B_OUTBYTES ) return -1;

  memset( S->buf, 0, sizeof( S->buf ) );
  S->buflen = 0;

  if( blake2bp_init_root( S->R, ( uint8_t ) outlen, 0 ) < 0 )
    return -1;

  for( size_t i = 0; i < PARALLELISM_DEGREE; ++i )
    if( blake2bp_init_leaf( S->S[i], ( uint8_t ) outlen, 0, i ) < 0 ) return -1;

  S->R->last_node = 1;
  S->S[PARALLELISM_DEGREE - 1]->last_node = 1;
  S->outlen = ( uint8_t ) outlen;
  return 0;
}