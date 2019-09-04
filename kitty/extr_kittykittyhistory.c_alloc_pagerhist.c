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
struct TYPE_5__ {unsigned int maxsz; int bufsize; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  Py_UCS4 ;
typedef  TYPE_1__ PagerHistoryBuf ;

/* Variables and functions */
 TYPE_1__* PyMem_Calloc (int,int) ; 
 int /*<<< orphan*/  PyMem_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  PyMem_RawMalloc (int) ; 

__attribute__((used)) static inline PagerHistoryBuf*
alloc_pagerhist(unsigned int pagerhist_sz) {
    PagerHistoryBuf *ph;
    if (!pagerhist_sz) return NULL;
    ph = PyMem_Calloc(1, sizeof(PagerHistoryBuf));
    if (!ph) return NULL;
    ph->maxsz = pagerhist_sz / sizeof(Py_UCS4);
    ph->bufsize = 1024*1024 / sizeof(Py_UCS4);
    ph->buffer = PyMem_RawMalloc(1024*1024);
    if (!ph->buffer) { PyMem_Free(ph); return NULL; }
    return ph;
}