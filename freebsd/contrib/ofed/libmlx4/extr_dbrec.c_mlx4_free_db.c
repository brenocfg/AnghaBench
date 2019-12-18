#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {void* buf; } ;
struct mlx4_db_page {unsigned long* free; TYPE_4__ buf; TYPE_2__* prev; struct mlx4_db_page* next; int /*<<< orphan*/  use_cnt; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct mlx4_context {int /*<<< orphan*/  db_list_mutex; struct mlx4_db_page** db_list; TYPE_1__ ibv_ctx; } ;
typedef  enum mlx4_db_type { ____Placeholder_mlx4_db_type } mlx4_db_type ;
struct TYPE_7__ {uintptr_t page_size; } ;
struct TYPE_6__ {struct mlx4_db_page* next; } ;

/* Variables and functions */
 int* db_size ; 
 int /*<<< orphan*/  free (struct mlx4_db_page*) ; 
 int /*<<< orphan*/  mlx4_free_buf (TYPE_4__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* to_mdev (int /*<<< orphan*/ ) ; 

void mlx4_free_db(struct mlx4_context *context, enum mlx4_db_type type, uint32_t *db)
{
	struct mlx4_db_page *page;
	uintptr_t ps = to_mdev(context->ibv_ctx.device)->page_size;
	int i;

	pthread_mutex_lock(&context->db_list_mutex);

	for (page = context->db_list[type]; page; page = page->next)
		if (((uintptr_t) db & ~(ps - 1)) == (uintptr_t) page->buf.buf)
			break;

	if (!page)
		goto out;

	i = ((void *) db - page->buf.buf) / db_size[type];
	page->free[i / (8 * sizeof (long))] |= 1UL << (i % (8 * sizeof (long)));

	if (!--page->use_cnt) {
		if (page->prev)
			page->prev->next = page->next;
		else
			context->db_list[type] = page->next;
		if (page->next)
			page->next->prev = page->prev;

		mlx4_free_buf(&page->buf);
		free(page);
	}

out:
	pthread_mutex_unlock(&context->db_list_mutex);
}