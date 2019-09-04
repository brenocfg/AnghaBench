#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t bufsize; size_t maxsz; void* buffer; } ;
typedef  int /*<<< orphan*/  Py_UCS4 ;
typedef  TYPE_1__ PagerHistoryBuf ;

/* Variables and functions */
 size_t MAX (int,size_t) ; 
 void* PyMem_Realloc (void*,size_t) ; 

__attribute__((used)) static inline bool
pagerhist_extend(PagerHistoryBuf *ph, size_t minsz) {
    if (ph->bufsize >= ph->maxsz) return false;
    size_t newsz = ph->bufsize + MAX(1024 * 1024, minsz);
    void *newbuf = PyMem_Realloc(ph->buffer, newsz * sizeof(Py_UCS4));
    if (!newbuf) return false;
    ph->buffer = newbuf;
    ph->bufsize = newsz;
    return true;
}