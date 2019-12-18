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
#define  BIO_CTRL_DUP 133 
#define  BIO_CTRL_FLUSH 132 
#define  BIO_CTRL_GET_CLOSE 131 
#define  BIO_CTRL_PENDING 130 
#define  BIO_CTRL_SET_CLOSE 129 
#define  BIO_CTRL_WPENDING 128 
 long BIO_get_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_shutdown (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static long
bio_rwcount_ctrl(BIO *b, int cmd, long num, void *ptr)
{
	long ret = 0;
	switch (cmd) {
	case BIO_CTRL_GET_CLOSE:
		ret = BIO_get_shutdown(b);
		break;
	case BIO_CTRL_SET_CLOSE:
		BIO_set_shutdown(b, (int)num);
		break;
	case BIO_CTRL_PENDING:
		ret = 0;
		break;
	case BIO_CTRL_WPENDING:
		ret = 0;
		break;
	case BIO_CTRL_DUP:
	case BIO_CTRL_FLUSH:
		ret = 1;
		break;
	}
	return ret;
}