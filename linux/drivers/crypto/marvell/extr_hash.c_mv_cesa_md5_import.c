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
struct md5_state {int /*<<< orphan*/  block; int /*<<< orphan*/  byte_count; int /*<<< orphan*/  hash; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int mv_cesa_ahash_import (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv_cesa_md5_import(struct ahash_request *req, const void *in)
{
	const struct md5_state *in_state = in;

	return mv_cesa_ahash_import(req, in_state->hash, in_state->byte_count,
				    in_state->block);
}