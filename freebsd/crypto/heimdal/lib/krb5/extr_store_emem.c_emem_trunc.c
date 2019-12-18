#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int off_t ;
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ krb5_storage ;
struct TYPE_5__ {unsigned char* base; size_t size; unsigned char* ptr; int len; } ;
typedef  TYPE_2__ emem_storage ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 void* realloc (unsigned char*,int) ; 

__attribute__((used)) static int
emem_trunc(krb5_storage *sp, off_t offset)
{
    emem_storage *s = (emem_storage*)sp->data;
    /*
     * If offset is larget then current size, or current size is
     * shrunk more then half of the current size, adjust buffer.
     */
    if (offset == 0) {
	free(s->base);
	s->size = 0;
	s->base = NULL;
	s->ptr = NULL;
    } else if ((size_t)offset > s->size || (s->size / 2) > (size_t)offset) {
	void *base;
	size_t off;
	off = s->ptr - s->base;
	base = realloc(s->base, offset);
	if(base == NULL)
	    return ENOMEM;
	if ((size_t)offset > s->size)
	    memset((char *)base + s->size, 0, offset - s->size);
	s->size = offset;
	s->base = base;
	s->ptr = (unsigned char *)base + off;
    }
    s->len = offset;
    if ((s->ptr - s->base) > offset)
	s->ptr = s->base + offset;
    return 0;
}