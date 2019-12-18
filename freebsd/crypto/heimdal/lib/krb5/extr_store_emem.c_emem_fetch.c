#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* seek ) (TYPE_1__*,size_t,int /*<<< orphan*/ ) ;scalar_t__ data; } ;
typedef  TYPE_1__ krb5_storage ;
struct TYPE_6__ {size_t base; size_t len; size_t ptr; } ;
typedef  TYPE_2__ emem_storage ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  memmove (void*,size_t,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
emem_fetch(krb5_storage *sp, void *data, size_t size)
{
    emem_storage *s = (emem_storage*)sp->data;
    if((size_t)(s->base + s->len - s->ptr) < size)
	size = s->base + s->len - s->ptr;
    memmove(data, s->ptr, size);
    sp->seek(sp, size, SEEK_CUR);
    return size;
}