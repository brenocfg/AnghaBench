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
struct string_list_sort_ctx {int (* cmp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct string_list_item {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_items(const void *a, const void *b, void *ctx)
{
	struct string_list_sort_ctx *sort_ctx = ctx;
	const struct string_list_item *one = a;
	const struct string_list_item *two = b;
	return sort_ctx->cmp(one->string, two->string);
}