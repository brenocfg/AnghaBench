#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* buffer; } ;
struct TYPE_4__ {TYPE_3__* pagerhist; } ;
typedef  TYPE_1__ HistoryBuf ;

/* Variables and functions */
 int /*<<< orphan*/  PyMem_Free (TYPE_3__*) ; 

__attribute__((used)) static inline void
free_pagerhist(HistoryBuf *self) {
    if (self->pagerhist) PyMem_Free(self->pagerhist->buffer);
    PyMem_Free(self->pagerhist);
    self->pagerhist = NULL;
}