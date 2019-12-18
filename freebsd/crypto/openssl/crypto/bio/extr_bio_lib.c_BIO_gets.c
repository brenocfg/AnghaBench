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
struct TYPE_7__ {int /*<<< orphan*/ * callback_ex; int /*<<< orphan*/ * callback; TYPE_1__* method; int /*<<< orphan*/  init; } ;
struct TYPE_6__ {int (* bgets ) (TYPE_2__*,char*,int) ;} ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int BIO_CB_GETS ; 
 int BIO_CB_RETURN ; 
 int /*<<< orphan*/  BIO_F_BIO_GETS ; 
 int /*<<< orphan*/  BIO_R_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  BIO_R_UNINITIALIZED ; 
 int /*<<< orphan*/  BIO_R_UNSUPPORTED_METHOD ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_call_callback (TYPE_2__*,int,char*,int,int /*<<< orphan*/ ,long,int,size_t*) ; 
 int stub1 (TYPE_2__*,char*,int) ; 

int BIO_gets(BIO *b, char *buf, int size)
{
    int ret;
    size_t readbytes = 0;

    if ((b == NULL) || (b->method == NULL) || (b->method->bgets == NULL)) {
        BIOerr(BIO_F_BIO_GETS, BIO_R_UNSUPPORTED_METHOD);
        return -2;
    }

    if (size < 0) {
        BIOerr(BIO_F_BIO_GETS, BIO_R_INVALID_ARGUMENT);
        return 0;
    }

    if (b->callback != NULL || b->callback_ex != NULL) {
        ret = (int)bio_call_callback(b, BIO_CB_GETS, buf, size, 0, 0L, 1, NULL);
        if (ret <= 0)
            return ret;
    }

    if (!b->init) {
        BIOerr(BIO_F_BIO_GETS, BIO_R_UNINITIALIZED);
        return -2;
    }

    ret = b->method->bgets(b, buf, size);

    if (ret > 0) {
        readbytes = ret;
        ret = 1;
    }

    if (b->callback != NULL || b->callback_ex != NULL)
        ret = (int)bio_call_callback(b, BIO_CB_GETS | BIO_CB_RETURN, buf, size,
                                     0, 0L, ret, &readbytes);

    if (ret > 0) {
        /* Shouldn't happen */
        if (readbytes > (size_t)size)
            ret = -1;
        else
            ret = (int)readbytes;
    }

    return ret;
}