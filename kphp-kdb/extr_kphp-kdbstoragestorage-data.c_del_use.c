#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; struct TYPE_4__* next; struct TYPE_4__* prev; } ;
typedef  TYPE_1__ metafile_t ;

/* Variables and functions */
 size_t get_meta_bucket (TYPE_1__*) ; 
 int /*<<< orphan*/ * metafile_bucket_bytes ; 
 int /*<<< orphan*/  metafiles ; 
 int /*<<< orphan*/  metafiles_bytes ; 

__attribute__((used)) static void del_use (metafile_t *meta) {
  metafile_t *u = meta->prev, *v = meta->next;
  u->next = v;
  v->prev = u;
  meta->prev = meta->next = NULL;
  metafile_bucket_bytes[get_meta_bucket (meta)] -= meta->size;
  metafiles_bytes -= meta->size;
  metafiles--;
}