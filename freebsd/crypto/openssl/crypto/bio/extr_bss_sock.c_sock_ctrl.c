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
struct TYPE_4__ {int num; int shutdown; int init; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
#define  BIO_CTRL_DUP 133 
#define  BIO_CTRL_FLUSH 132 
#define  BIO_CTRL_GET_CLOSE 131 
#define  BIO_CTRL_SET_CLOSE 130 
#define  BIO_C_GET_FD 129 
#define  BIO_C_SET_FD 128 
 int /*<<< orphan*/  sock_free (TYPE_1__*) ; 

__attribute__((used)) static long sock_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    long ret = 1;
    int *ip;

    switch (cmd) {
    case BIO_C_SET_FD:
        sock_free(b);
        b->num = *((int *)ptr);
        b->shutdown = (int)num;
        b->init = 1;
        break;
    case BIO_C_GET_FD:
        if (b->init) {
            ip = (int *)ptr;
            if (ip != NULL)
                *ip = b->num;
            ret = b->num;
        } else
            ret = -1;
        break;
    case BIO_CTRL_GET_CLOSE:
        ret = b->shutdown;
        break;
    case BIO_CTRL_SET_CLOSE:
        b->shutdown = (int)num;
        break;
    case BIO_CTRL_DUP:
    case BIO_CTRL_FLUSH:
        ret = 1;
        break;
    default:
        ret = 0;
        break;
    }
    return ret;
}