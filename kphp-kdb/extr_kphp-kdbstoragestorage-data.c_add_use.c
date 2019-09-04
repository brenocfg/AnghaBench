#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ size; struct TYPE_5__* next; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ metafile_t ;

/* Variables and functions */
 int get_meta_bucket (TYPE_1__*) ; 
 TYPE_1__* lru_meta_lst ; 
 int /*<<< orphan*/ * metafile_bucket_bytes ; 
 int /*<<< orphan*/  metafiles ; 
 int /*<<< orphan*/  metafiles_bytes ; 

__attribute__((used)) static void add_use (metafile_t *meta) {
  const int n = get_meta_bucket (meta);
  metafile_t *u = &lru_meta_lst[n], *v = lru_meta_lst[n].next;
  u->next = meta; meta->prev = u;
  v->prev = meta; meta->next = v;
  metafile_bucket_bytes[n] += meta->size;
  metafiles_bytes += meta->size;
  metafiles++;
}