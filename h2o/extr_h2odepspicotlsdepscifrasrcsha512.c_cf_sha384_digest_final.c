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
typedef  int /*<<< orphan*/  cf_sha512_context ;

/* Variables and functions */
 int /*<<< orphan*/  CF_SHA384_HASHSZ ; 
 int CF_SHA512_HASHSZ ; 
 int /*<<< orphan*/  cf_sha512_digest_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cf_sha384_digest_final(cf_sha512_context *ctx, uint8_t hash[CF_SHA384_HASHSZ])
{
  uint8_t full[CF_SHA512_HASHSZ];
  cf_sha512_digest_final(ctx, full);
  memcpy(hash, full, CF_SHA384_HASHSZ);
}