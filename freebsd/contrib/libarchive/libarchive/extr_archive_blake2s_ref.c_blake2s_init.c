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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  blake2s_state ;
struct TYPE_3__ {int fanout; int depth; int /*<<< orphan*/  personal; int /*<<< orphan*/  salt; scalar_t__ inner_length; scalar_t__ node_depth; int /*<<< orphan*/  xof_length; int /*<<< orphan*/  node_offset; int /*<<< orphan*/  leaf_length; scalar_t__ key_length; scalar_t__ digest_length; } ;
typedef  TYPE_1__ blake2s_param ;

/* Variables and functions */
 size_t BLAKE2S_OUTBYTES ; 
 int blake2s_init_param (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int blake2s_init( blake2s_state *S, size_t outlen )
{
  blake2s_param P[1];

  /* Move interval verification here? */
  if ( ( !outlen ) || ( outlen > BLAKE2S_OUTBYTES ) ) return -1;

  P->digest_length = (uint8_t)outlen;
  P->key_length    = 0;
  P->fanout        = 1;
  P->depth         = 1;
  store32( &P->leaf_length, 0 );
  store32( &P->node_offset, 0 );
  store16( &P->xof_length, 0 );
  P->node_depth    = 0;
  P->inner_length  = 0;
  /* memset(P->reserved, 0, sizeof(P->reserved) ); */
  memset( P->salt,     0, sizeof( P->salt ) );
  memset( P->personal, 0, sizeof( P->personal ) );
  return blake2s_init_param( S, P );
}