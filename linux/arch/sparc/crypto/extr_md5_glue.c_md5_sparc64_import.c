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
struct shash_desc {int dummy; } ;
struct md5_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct md5_state*,void const*,int) ; 
 struct md5_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int md5_sparc64_import(struct shash_desc *desc, const void *in)
{
	struct md5_state *sctx = shash_desc_ctx(desc);

	memcpy(sctx, in, sizeof(*sctx));

	return 0;
}