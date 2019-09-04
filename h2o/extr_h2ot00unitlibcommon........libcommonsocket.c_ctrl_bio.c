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
#define  BIO_CTRL_FLUSH 130 
#define  BIO_CTRL_GET_CLOSE 129 
#define  BIO_CTRL_SET_CLOSE 128 
 long BIO_get_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_shutdown (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static long ctrl_bio(BIO *b, int cmd, long num, void *ptr)
{
    switch (cmd) {
    case BIO_CTRL_GET_CLOSE:
        return BIO_get_shutdown(b);
    case BIO_CTRL_SET_CLOSE:
        BIO_set_shutdown(b, (int)num);
        return 1;
    case BIO_CTRL_FLUSH:
        return 1;
    default:
        return 0;
    }
}