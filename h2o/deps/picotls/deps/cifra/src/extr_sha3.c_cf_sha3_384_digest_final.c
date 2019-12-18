#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  cf_sha3_context ;

/* Variables and functions */
 int /*<<< orphan*/  CF_SHA3_384_HASHSZ ; 
 int /*<<< orphan*/  pad_and_squeeze (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cf_sha3_384_digest_final(cf_sha3_context *ctx, uint8_t hash[CF_SHA3_384_HASHSZ])
{
  pad_and_squeeze(ctx, hash, CF_SHA3_384_HASHSZ);
}