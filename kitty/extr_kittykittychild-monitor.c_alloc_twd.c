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
struct TYPE_4__ {size_t sz; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ ThreadWriteData ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 void* malloc (size_t) ; 

__attribute__((used)) static inline ThreadWriteData*
alloc_twd(size_t sz) {
    ThreadWriteData *data = malloc(sizeof(ThreadWriteData));
    if (data != NULL) {
        data->sz = sz;
        data->buf = malloc(sz);
        if (data->buf == NULL) { free(data); data = NULL; }
    }
    return data;
}