#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * next_bio; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
#define  BIO_CTRL_DUP 129 
#define  BIO_C_DO_STATE_MACHINE 128 
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (TYPE_1__*) ; 
 long BIO_ctrl (int /*<<< orphan*/ *,int,long,void*) ; 

__attribute__((used)) static long nullf_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    long ret;

    if (b->next_bio == NULL)
        return 0;
    switch (cmd) {
    case BIO_C_DO_STATE_MACHINE:
        BIO_clear_retry_flags(b);
        ret = BIO_ctrl(b->next_bio, cmd, num, ptr);
        BIO_copy_next_retry(b);
        break;
    case BIO_CTRL_DUP:
        ret = 0L;
        break;
    default:
        ret = BIO_ctrl(b->next_bio, cmd, num, ptr);
    }
    return ret;
}