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
struct TYPE_4__ {scalar_t__ refcnt; struct TYPE_4__* prev; } ;
typedef  TYPE_1__ metafile_t ;

/* Variables and functions */
 TYPE_1__* lru_meta_lst ; 
 scalar_t__ max_metafiles_bytes ; 
 scalar_t__* metafile_bucket_bytes ; 
 int /*<<< orphan*/  metafile_free (TYPE_1__*) ; 
 int /*<<< orphan*/  metafiles ; 
 int /*<<< orphan*/  vkprintf (int,char*,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unload_metafiles (int n) {
  int t = 0;
  metafile_t *p, *w;
  for (p = lru_meta_lst[n].prev; p != &lru_meta_lst[n] && metafile_bucket_bytes[n] > max_metafiles_bytes; ) {
    if (p->refcnt > 0) {
      p = p->prev;
      continue;
    }
    w = p->prev;
    metafile_free (p);
    t++;
    p = w;
  }

  if (metafile_bucket_bytes[n] > max_metafiles_bytes && !t) {
    vkprintf (2, "unload_metafile: max_metafiles_bytes = %d, metafile_bucket_bytes[%d] = %d, metafiles = %d\n", max_metafiles_bytes, n, metafile_bucket_bytes[n], metafiles);
  }
}