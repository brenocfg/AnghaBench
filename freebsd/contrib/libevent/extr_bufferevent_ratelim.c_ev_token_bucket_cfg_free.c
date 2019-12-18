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
struct ev_token_bucket_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mm_free (struct ev_token_bucket_cfg*) ; 

void
ev_token_bucket_cfg_free(struct ev_token_bucket_cfg *cfg)
{
	mm_free(cfg);
}