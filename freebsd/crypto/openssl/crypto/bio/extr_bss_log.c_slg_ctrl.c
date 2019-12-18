#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
#define  BIO_CTRL_SET 128 
 int /*<<< orphan*/  xcloselog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xopenlog (int /*<<< orphan*/ *,void*,long) ; 

__attribute__((used)) static long slg_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    switch (cmd) {
    case BIO_CTRL_SET:
        xcloselog(b);
        xopenlog(b, ptr, num);
        break;
    default:
        break;
    }
    return 0;
}