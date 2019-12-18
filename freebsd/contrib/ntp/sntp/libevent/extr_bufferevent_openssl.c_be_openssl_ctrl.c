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
union bufferevent_ctrl_data {int fd; int /*<<< orphan*/  ptr; } ;
struct bufferevent_openssl {int fd_is_set; int /*<<< orphan*/  underlying; int /*<<< orphan*/  state; int /*<<< orphan*/  ssl; } ;
struct bufferevent {int /*<<< orphan*/  ev_read; } ;
typedef  enum bufferevent_ctrl_op { ____Placeholder_bufferevent_ctrl_op } bufferevent_ctrl_op ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
#define  BEV_CTRL_CANCEL_ALL 131 
#define  BEV_CTRL_GET_FD 130 
#define  BEV_CTRL_GET_UNDERLYING 129 
#define  BEV_CTRL_SET_FD 128 
 int /*<<< orphan*/ * BIO_new_socket (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUFFEREVENT_SSL_OPEN ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int event_get_fd (int /*<<< orphan*/ *) ; 
 int set_handshake_callbacks (struct bufferevent_openssl*,int) ; 
 int set_open_callbacks (struct bufferevent_openssl*,int) ; 
 struct bufferevent_openssl* upcast (struct bufferevent*) ; 

__attribute__((used)) static int
be_openssl_ctrl(struct bufferevent *bev,
    enum bufferevent_ctrl_op op, union bufferevent_ctrl_data *data)
{
	struct bufferevent_openssl *bev_ssl = upcast(bev);
	switch (op) {
	case BEV_CTRL_SET_FD:
		if (bev_ssl->underlying)
			return -1;
		{
			BIO *bio;
			bio = BIO_new_socket(data->fd, 0);
			SSL_set_bio(bev_ssl->ssl, bio, bio);
			bev_ssl->fd_is_set = 1;
		}
		if (data->fd == -1)
			bev_ssl->fd_is_set = 0;
		if (bev_ssl->state == BUFFEREVENT_SSL_OPEN)
			return set_open_callbacks(bev_ssl, data->fd);
		else {
			return set_handshake_callbacks(bev_ssl, data->fd);
		}
	case BEV_CTRL_GET_FD:
		if (bev_ssl->underlying)
			return -1;
		if (!bev_ssl->fd_is_set)
			return -1;
		data->fd = event_get_fd(&bev->ev_read);
		return 0;
	case BEV_CTRL_GET_UNDERLYING:
		if (!bev_ssl->underlying)
			return -1;
		data->ptr = bev_ssl->underlying;
		return 0;
	case BEV_CTRL_CANCEL_ALL:
	default:
		return -1;
	}
}