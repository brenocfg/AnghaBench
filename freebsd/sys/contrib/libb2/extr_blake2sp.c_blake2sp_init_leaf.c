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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  outlen; } ;
typedef  TYPE_1__ blake2s_state ;
struct TYPE_7__ {int depth; int /*<<< orphan*/  inner_length; int /*<<< orphan*/  personal; int /*<<< orphan*/  salt; scalar_t__ node_depth; int /*<<< orphan*/  node_offset; scalar_t__ leaf_length; int /*<<< orphan*/  fanout; void* key_length; void* digest_length; } ;
typedef  TYPE_2__ blake2s_param ;

/* Variables and functions */
 int /*<<< orphan*/  BLAKE2S_OUTBYTES ; 
 int /*<<< orphan*/  PARALLELISM_DEGREE ; 
 int /*<<< orphan*/  blake2s_init_param (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store48 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blake2sp_init_leaf( blake2s_state *S, uint8_t outlen, uint8_t keylen, uint64_t offset )
{
  blake2s_param P[1];
  P->digest_length = outlen;
  P->key_length = keylen;
  P->fanout = PARALLELISM_DEGREE;
  P->depth = 2;
  P->leaf_length = 0;
  store48( P->node_offset, offset );
  P->node_depth = 0;
  P->inner_length = BLAKE2S_OUTBYTES;
  memset( P->salt, 0, sizeof( P->salt ) );
  memset( P->personal, 0, sizeof( P->personal ) );
  blake2s_init_param( S, P );
  S->outlen = P->inner_length;
  return 0;
}