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
struct evrpc_meta_list {int dummy; } ;
struct evrpc_meta {struct evrpc_meta* data; struct evrpc_meta* key; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 struct evrpc_meta* TAILQ_FIRST (struct evrpc_meta_list*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct evrpc_meta_list*,struct evrpc_meta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_free (struct evrpc_meta*) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static void
evrpc_meta_data_free(struct evrpc_meta_list *meta_data)
{
	struct evrpc_meta *entry;
	EVUTIL_ASSERT(meta_data != NULL);

	while ((entry = TAILQ_FIRST(meta_data)) != NULL) {
		TAILQ_REMOVE(meta_data, entry, next);
		mm_free(entry->key);
		mm_free(entry->data);
		mm_free(entry);
	}
}