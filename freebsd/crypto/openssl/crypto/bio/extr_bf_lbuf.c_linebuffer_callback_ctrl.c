#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * next_bio; } ;
typedef  int /*<<< orphan*/  BIO_info_cb ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 long BIO_callback_ctrl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long linebuffer_callback_ctrl(BIO *b, int cmd, BIO_info_cb *fp)
{
    long ret = 1;

    if (b->next_bio == NULL)
        return 0;
    switch (cmd) {
    default:
        ret = BIO_callback_ctrl(b->next_bio, cmd, fp);
        break;
    }
    return ret;
}