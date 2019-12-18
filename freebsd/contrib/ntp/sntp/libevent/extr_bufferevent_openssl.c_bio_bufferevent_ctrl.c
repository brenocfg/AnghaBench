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
struct bufferevent {int dummy; } ;
struct TYPE_3__ {long shutdown; struct bufferevent* ptr; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
#define  BIO_CTRL_DUP 133 
#define  BIO_CTRL_FLUSH 132 
#define  BIO_CTRL_GET_CLOSE 131 
#define  BIO_CTRL_PENDING 130 
#define  BIO_CTRL_SET_CLOSE 129 
#define  BIO_CTRL_WPENDING 128 
 int /*<<< orphan*/  bufferevent_get_input (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_get_output (struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_get_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long
bio_bufferevent_ctrl(BIO *b, int cmd, long num, void *ptr)
{
	struct bufferevent *bufev = b->ptr;
	long ret = 1;

	switch (cmd) {
	case BIO_CTRL_GET_CLOSE:
		ret = b->shutdown;
		break;
	case BIO_CTRL_SET_CLOSE:
		b->shutdown = (int)num;
		break;
	case BIO_CTRL_PENDING:
		ret = evbuffer_get_length(bufferevent_get_input(bufev)) != 0;
		break;
	case BIO_CTRL_WPENDING:
		ret = evbuffer_get_length(bufferevent_get_output(bufev)) != 0;
		break;
	/* XXXX These two are given a special-case treatment because
	 * of cargo-cultism.  I should come up with a better reason. */
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