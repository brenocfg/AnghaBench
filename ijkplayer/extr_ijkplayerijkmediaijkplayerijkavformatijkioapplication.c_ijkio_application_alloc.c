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
struct TYPE_4__ {void* opaque; } ;
typedef  TYPE_1__ IjkIOApplicationContext ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 

int  ijkio_application_alloc(IjkIOApplicationContext **ph, void *opaque) {
    IjkIOApplicationContext *h = NULL;

    h = calloc(1, sizeof(IjkIOApplicationContext));
    if (!h)
        return -1;

    h->opaque = opaque;

    *ph = h;
    return 0;
}