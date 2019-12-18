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
struct spu_gang {int /*<<< orphan*/  mutex; int /*<<< orphan*/  contexts; int /*<<< orphan*/  list; } ;
struct spu_context {int /*<<< orphan*/  gang_list; int /*<<< orphan*/  gang; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_spu_gang (struct spu_gang*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void spu_gang_add_ctx(struct spu_gang *gang, struct spu_context *ctx)
{
	mutex_lock(&gang->mutex);
	ctx->gang = get_spu_gang(gang);
	list_add(&ctx->gang_list, &gang->list);
	gang->contexts++;
	mutex_unlock(&gang->mutex);
}