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
struct evrpc_request_wrapper {struct evrpc_hook_meta* hook_meta; } ;
struct evrpc_meta {size_t data_size; int /*<<< orphan*/ * data; int /*<<< orphan*/ * key; } ;
struct evrpc_hook_meta {int /*<<< orphan*/  meta_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct evrpc_meta*,int /*<<< orphan*/ ) ; 
 struct evrpc_hook_meta* evrpc_hook_meta_new_ () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 void* mm_malloc (size_t) ; 
 int /*<<< orphan*/ * mm_strdup (char const*) ; 
 int /*<<< orphan*/  next ; 

void
evrpc_hook_add_meta(void *ctx, const char *key,
    const void *data, size_t data_size)
{
	struct evrpc_request_wrapper *req = ctx;
	struct evrpc_hook_meta *store = NULL;
	struct evrpc_meta *meta = NULL;

	if ((store = req->hook_meta) == NULL)
		store = req->hook_meta = evrpc_hook_meta_new_();

	meta = mm_malloc(sizeof(struct evrpc_meta));
	EVUTIL_ASSERT(meta != NULL);
	meta->key = mm_strdup(key);
	EVUTIL_ASSERT(meta->key != NULL);
	meta->data_size = data_size;
	meta->data = mm_malloc(data_size);
	EVUTIL_ASSERT(meta->data != NULL);
	memcpy(meta->data, data, data_size);

	TAILQ_INSERT_TAIL(&store->meta_data, meta, next);
}