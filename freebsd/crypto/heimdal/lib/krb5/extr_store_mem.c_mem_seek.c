#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int off_t ;
struct TYPE_6__ {size_t size; int ptr; int base; } ;
typedef  TYPE_1__ mem_storage ;
struct TYPE_7__ {int (* seek ) (TYPE_2__*,int,int const) ;scalar_t__ data; } ;
typedef  TYPE_2__ krb5_storage ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  errno ; 
 int stub1 (TYPE_2__*,int,int const) ; 
 int stub2 (TYPE_2__*,int,int const) ; 

__attribute__((used)) static off_t
mem_seek(krb5_storage *sp, off_t offset, int whence)
{
    mem_storage *s = (mem_storage*)sp->data;
    switch(whence){
    case SEEK_SET:
	if((size_t)offset > s->size)
	    offset = s->size;
	if(offset < 0)
	    offset = 0;
	s->ptr = s->base + offset;
	break;
    case SEEK_CUR:
	return sp->seek(sp, s->ptr - s->base + offset, SEEK_SET);
    case SEEK_END:
	return sp->seek(sp, s->size + offset, SEEK_SET);
    default:
	errno = EINVAL;
	return -1;
    }
    return s->ptr - s->base;
}