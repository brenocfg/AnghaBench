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
struct TYPE_6__ {int (* func_read ) (TYPE_2__*,void*,size_t,int /*<<< orphan*/ *) ;int (* func_write ) (TYPE_2__*,void*,size_t,int /*<<< orphan*/ *) ;int (* func_other ) (TYPE_2__*) ;} ;
struct ssl_async_args {size_t num; int type; TYPE_1__ f; void* buf; TYPE_2__* s; } ;
struct TYPE_7__ {int /*<<< orphan*/  asyncrw; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
#define  OTHERFUNC 130 
#define  READFUNC 129 
#define  WRITEFUNC 128 
 int stub1 (TYPE_2__*,void*,size_t,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_2__*,void*,size_t,int /*<<< orphan*/ *) ; 
 int stub3 (TYPE_2__*) ; 

__attribute__((used)) static int ssl_io_intern(void *vargs)
{
    struct ssl_async_args *args;
    SSL *s;
    void *buf;
    size_t num;

    args = (struct ssl_async_args *)vargs;
    s = args->s;
    buf = args->buf;
    num = args->num;
    switch (args->type) {
    case READFUNC:
        return args->f.func_read(s, buf, num, &s->asyncrw);
    case WRITEFUNC:
        return args->f.func_write(s, buf, num, &s->asyncrw);
    case OTHERFUNC:
        return args->f.func_other(s);
    }
    return -1;
}