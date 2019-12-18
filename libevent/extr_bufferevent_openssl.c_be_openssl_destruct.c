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
struct TYPE_2__ {int options; } ;
struct bufferevent_openssl {int /*<<< orphan*/  ssl; int /*<<< orphan*/  underlying; TYPE_1__ bev; } ;
struct bufferevent {int dummy; } ;
typedef  scalar_t__ evutil_socket_t ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BEV_OPT_CLOSE_ON_FREE ; 
 scalar_t__ BIO_get_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVUTIL_INVALID_SOCKET ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SSL_get_wbio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_closesocket (scalar_t__) ; 
 struct bufferevent_openssl* upcast (struct bufferevent*) ; 

__attribute__((used)) static void
be_openssl_destruct(struct bufferevent *bev)
{
	struct bufferevent_openssl *bev_ssl = upcast(bev);

	if (bev_ssl->bev.options & BEV_OPT_CLOSE_ON_FREE) {
		if (! bev_ssl->underlying) {
			evutil_socket_t fd = EVUTIL_INVALID_SOCKET;
			BIO *bio = SSL_get_wbio(bev_ssl->ssl);
			if (bio)
				fd = BIO_get_fd(bio, NULL);
			if (fd >= 0)
				evutil_closesocket(fd);
		}
		SSL_free(bev_ssl->ssl);
	}
}