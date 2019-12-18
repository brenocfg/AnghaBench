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
struct ix_sa_dir {scalar_t__ npe_mode; scalar_t__ npe_ctx_idx; int /*<<< orphan*/  npe_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPE_CTX_LEN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_sa_dir(struct ix_sa_dir *dir)
{
	memset(dir->npe_ctx, 0, NPE_CTX_LEN);
	dir->npe_ctx_idx = 0;
	dir->npe_mode = 0;
}