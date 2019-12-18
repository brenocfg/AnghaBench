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
struct TYPE_5__ {size_t base; size_t size; size_t ptr; } ;
typedef  TYPE_1__ mem_storage ;
struct TYPE_6__ {int /*<<< orphan*/  (* seek ) (TYPE_2__*,size_t,int /*<<< orphan*/ ) ;scalar_t__ data; } ;
typedef  TYPE_2__ krb5_storage ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  memmove (size_t,void const*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
mem_store(krb5_storage *sp, const void *data, size_t size)
{
    mem_storage *s = (mem_storage*)sp->data;
    if(size > (size_t)(s->base + s->size - s->ptr))
	size = s->base + s->size - s->ptr;
    memmove(s->ptr, data, size);
    sp->seek(sp, size, SEEK_CUR);
    return size;
}