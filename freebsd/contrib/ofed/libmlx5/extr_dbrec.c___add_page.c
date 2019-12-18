#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_db_page {int num_db; struct mlx5_db_page* prev; struct mlx5_db_page* next; int /*<<< orphan*/ * free; scalar_t__ use_cnt; int /*<<< orphan*/  buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct mlx5_context {int cache_line_size; struct mlx5_db_page* db_list; TYPE_1__ ibv_ctx; } ;
struct TYPE_4__ {int page_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mlx5_db_page*) ; 
 struct mlx5_db_page* malloc (int) ; 
 scalar_t__ mlx5_alloc_buf (int /*<<< orphan*/ *,int,int) ; 
 TYPE_2__* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5_db_page *__add_page(struct mlx5_context *context)
{
	struct mlx5_db_page *page;
	int ps = to_mdev(context->ibv_ctx.device)->page_size;
	int pp;
	int i;
	int nlong;

	pp = ps / context->cache_line_size;
	nlong = (pp + 8 * sizeof(long) - 1) / (8 * sizeof(long));

	page = malloc(sizeof *page + nlong * sizeof(long));
	if (!page)
		return NULL;

	if (mlx5_alloc_buf(&page->buf, ps, ps)) {
		free(page);
		return NULL;
	}

	page->num_db  = pp;
	page->use_cnt = 0;
	for (i = 0; i < nlong; ++i)
		page->free[i] = ~0;

	page->prev = NULL;
	page->next = context->db_list;
	context->db_list = page;
	if (page->next)
		page->next->prev = page;

	return page;
}