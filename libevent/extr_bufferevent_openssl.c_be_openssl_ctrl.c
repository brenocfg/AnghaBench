#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union bufferevent_ctrl_data {TYPE_1__* ptr; void* fd; } ;
struct bufferevent_openssl {TYPE_1__* underlying; int /*<<< orphan*/  old_state; int /*<<< orphan*/  ssl; } ;
struct bufferevent {int /*<<< orphan*/  ev_read; } ;
typedef  enum bufferevent_ctrl_op { ____Placeholder_bufferevent_ctrl_op } bufferevent_ctrl_op ;
struct TYPE_2__ {int /*<<< orphan*/  ev_read; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
#define  BEV_CTRL_CANCEL_ALL 131 
#define  BEV_CTRL_GET_FD 130 
#define  BEV_CTRL_GET_UNDERLYING 129 
#define  BEV_CTRL_SET_FD 128 
 int /*<<< orphan*/ * BIO_new_bufferevent (TYPE_1__*) ; 
 int /*<<< orphan*/ * BIO_new_socket (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int be_openssl_set_fd (struct bufferevent_openssl*,int /*<<< orphan*/ ,void*) ; 
 void* event_get_fd (int /*<<< orphan*/ *) ; 
 struct bufferevent_openssl* upcast (struct bufferevent*) ; 

__attribute__((used)) static int
be_openssl_ctrl(struct bufferevent *bev,
    enum bufferevent_ctrl_op op, union bufferevent_ctrl_data *data)
{
	struct bufferevent_openssl *bev_ssl = upcast(bev);
	switch (op) {
	case BEV_CTRL_SET_FD:
		if (!bev_ssl->underlying) {
			BIO *bio;
			bio = BIO_new_socket((int)data->fd, 0);
			SSL_set_bio(bev_ssl->ssl, bio, bio);
		} else {
			BIO *bio;
			if (!(bio = BIO_new_bufferevent(bev_ssl->underlying)))
				return -1;
			SSL_set_bio(bev_ssl->ssl, bio, bio);
		}

		return be_openssl_set_fd(bev_ssl, bev_ssl->old_state, data->fd);
	case BEV_CTRL_GET_FD:
		if (bev_ssl->underlying) {
			data->fd = event_get_fd(&bev_ssl->underlying->ev_read);
		} else {
			data->fd = event_get_fd(&bev->ev_read);
		}
		return 0;
	case BEV_CTRL_GET_UNDERLYING:
		data->ptr = bev_ssl->underlying;
		return 0;
	case BEV_CTRL_CANCEL_ALL:
	default:
		return -1;
	}
}