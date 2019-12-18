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
typedef  int /*<<< orphan*/  u128 ;
typedef  int /*<<< orphan*/  le128 ;

/* Variables and functions */
 int /*<<< orphan*/  GLUE_FUNC_CAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cast6_encrypt ; 
 int /*<<< orphan*/  glue_xts_crypt_128bit_one (void*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cast6_xts_enc(void *ctx, u128 *dst, const u128 *src, le128 *iv)
{
	glue_xts_crypt_128bit_one(ctx, dst, src, iv,
				  GLUE_FUNC_CAST(__cast6_encrypt));
}