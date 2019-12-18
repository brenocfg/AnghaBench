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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  blake2s_state ;
struct TYPE_3__ {int depth; int /*<<< orphan*/  personal; int /*<<< orphan*/  salt; int /*<<< orphan*/  inner_length; scalar_t__ node_depth; int /*<<< orphan*/  xof_length; int /*<<< orphan*/  node_offset; int /*<<< orphan*/  leaf_length; int /*<<< orphan*/  fanout; void* key_length; void* digest_length; } ;
typedef  TYPE_1__ blake2s_param ;

/* Variables and functions */
 int /*<<< orphan*/  BLAKE2S_OUTBYTES ; 
 int /*<<< orphan*/  PARALLELISM_DEGREE ; 
 int blake2sp_init_leaf_param (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blake2sp_init_leaf( blake2s_state *S, size_t outlen, size_t keylen, uint32_t offset )
{
  blake2s_param P[1];
  P->digest_length = (uint8_t)outlen;
  P->key_length = (uint8_t)keylen;
  P->fanout = PARALLELISM_DEGREE;
  P->depth = 2;
  store32( &P->leaf_length, 0 );
  store32( &P->node_offset, offset );
  store16( &P->xof_length, 0 );
  P->node_depth = 0;
  P->inner_length = BLAKE2S_OUTBYTES;
  memset( P->salt, 0, sizeof( P->salt ) );
  memset( P->personal, 0, sizeof( P->personal ) );
  return blake2sp_init_leaf_param( S, P );
}