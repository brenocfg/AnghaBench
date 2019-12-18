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

/* Variables and functions */
 int /*<<< orphan*/  deflate_comp_exit (void*) ; 
 int deflate_comp_init (void*,int) ; 
 int deflate_decomp_init (void*,int) ; 

__attribute__((used)) static int __deflate_init(void *ctx, int format)
{
	int ret;

	ret = deflate_comp_init(ctx, format);
	if (ret)
		goto out;
	ret = deflate_decomp_init(ctx, format);
	if (ret)
		deflate_comp_exit(ctx);
out:
	return ret;
}