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
struct xcbc_state {int dummy; } ;
struct shash_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct xcbc_state*,int /*<<< orphan*/ ,int) ; 
 struct xcbc_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int nx_xcbc_init(struct shash_desc *desc)
{
	struct xcbc_state *sctx = shash_desc_ctx(desc);

	memset(sctx, 0, sizeof *sctx);

	return 0;
}