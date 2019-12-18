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
typedef  int ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* seek ) (TYPE_1__*,size_t,int /*<<< orphan*/ ) ;scalar_t__ data; } ;
typedef  TYPE_1__ krb5_storage ;
struct TYPE_6__ {unsigned char* base; int size; unsigned char* ptr; } ;
typedef  TYPE_2__ emem_storage ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  memmove (unsigned char*,void const*,size_t) ; 
 void* realloc (unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
emem_store(krb5_storage *sp, const void *data, size_t size)
{
    emem_storage *s = (emem_storage*)sp->data;
    if(size > (size_t)(s->base + s->size - s->ptr)){
	void *base;
	size_t sz, off;
	off = s->ptr - s->base;
	sz = off + size;
	if (sz < 4096)
	    sz *= 2;
	base = realloc(s->base, sz);
	if(base == NULL)
	    return -1;
	s->size = sz;
	s->base = base;
	s->ptr = (unsigned char*)base + off;
    }
    memmove(s->ptr, data, size);
    sp->seek(sp, size, SEEK_CUR);
    return size;
}