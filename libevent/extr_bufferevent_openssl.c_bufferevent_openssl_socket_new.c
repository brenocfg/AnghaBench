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
struct event_base {int dummy; } ;
struct bufferevent {int dummy; } ;
typedef  scalar_t__ evutil_socket_t ;
typedef  enum bufferevent_ssl_state { ____Placeholder_bufferevent_ssl_state } bufferevent_ssl_state ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BEV_OPT_CLOSE_ON_FREE ; 
 long BIO_get_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_socket (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_wbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bufferevent* bufferevent_openssl_new_impl (struct event_base*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int,int) ; 

struct bufferevent *
bufferevent_openssl_socket_new(struct event_base *base,
    evutil_socket_t fd,
    SSL *ssl,
    enum bufferevent_ssl_state state,
    int options)
{
	/* Does the SSL already have an fd? */
	BIO *bio = SSL_get_wbio(ssl);
	long have_fd = -1;

	if (bio)
		have_fd = BIO_get_fd(bio, NULL);

	if (have_fd >= 0) {
		/* The SSL is already configured with an fd. */
		if (fd < 0) {
			/* We should learn the fd from the SSL. */
			fd = (evutil_socket_t) have_fd;
		} else if (have_fd == (long)fd) {
			/* We already know the fd from the SSL; do nothing */
		} else {
			/* We specified an fd different from that of the SSL.
			   This is probably an error on our part.  Fail. */
			goto err;
		}
		BIO_set_close(bio, 0);
	} else {
		/* The SSL isn't configured with a BIO with an fd. */
		if (fd >= 0) {
			/* ... and we have an fd we want to use. */
			bio = BIO_new_socket((int)fd, 0);
			SSL_set_bio(ssl, bio, bio);
		} else {
			/* Leave the fd unset. */
		}
	}

	return bufferevent_openssl_new_impl(
		base, NULL, fd, ssl, state, options);

err:
	if (options & BEV_OPT_CLOSE_ON_FREE)
		SSL_free(ssl);
	return NULL;
}