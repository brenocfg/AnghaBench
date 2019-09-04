#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int index_type ;
struct TYPE_6__ {int maxsz; } ;
struct TYPE_5__ {TYPE_4__* pagerhist; } ;
typedef  int /*<<< orphan*/  Py_UCS4 ;
typedef  TYPE_1__ HistoryBuf ;

/* Variables and functions */
 TYPE_4__* alloc_pagerhist (int) ; 
 int /*<<< orphan*/  free_pagerhist (TYPE_1__*) ; 

__attribute__((used)) static inline void
pagerhist_clear(HistoryBuf *self) {
    if (!self->pagerhist || !self->pagerhist->maxsz) return;
    index_type pagerhist_sz = self->pagerhist->maxsz  * sizeof(Py_UCS4);
    free_pagerhist(self);
    self->pagerhist = alloc_pagerhist(pagerhist_sz);
}