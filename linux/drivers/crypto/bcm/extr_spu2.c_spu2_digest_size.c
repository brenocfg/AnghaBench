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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum hash_type { ____Placeholder_hash_type } hash_type ;
typedef  enum hash_alg { ____Placeholder_hash_alg } hash_alg ;

/* Variables and functions */

u32 spu2_digest_size(u32 alg_digest_size, enum hash_alg alg,
		     enum hash_type htype)
{
	return alg_digest_size;
}