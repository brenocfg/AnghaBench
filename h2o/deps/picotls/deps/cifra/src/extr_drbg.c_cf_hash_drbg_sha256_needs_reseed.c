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
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ reseed_counter; } ;
typedef  TYPE_1__ cf_hash_drbg_sha256 ;

/* Variables and functions */

uint32_t cf_hash_drbg_sha256_needs_reseed(const cf_hash_drbg_sha256 *ctx)
{
  /* we need reseeding after 2 ^ 32 - 1 requests. */
  return ctx->reseed_counter == 0;
}