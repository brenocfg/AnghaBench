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
typedef  enum bufferevent_ssl_state { ____Placeholder_bufferevent_ssl_state } bufferevent_ssl_state ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BEV_OPT_CLOSE_ON_FREE ; 
 int /*<<< orphan*/ * BIO_new_bufferevent (struct bufferevent*) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bufferevent* bufferevent_openssl_new_impl (struct event_base*,struct bufferevent*,int,int /*<<< orphan*/ *,int,int) ; 

struct bufferevent *
bufferevent_openssl_filter_new(struct event_base *base,
    struct bufferevent *underlying,
    SSL *ssl,
    enum bufferevent_ssl_state state,
    int options)
{
	BIO *bio;
	struct bufferevent *bev;

	if (!underlying)
		goto err;
	if (!(bio = BIO_new_bufferevent(underlying)))
		goto err;

	SSL_set_bio(ssl, bio, bio);

	bev = bufferevent_openssl_new_impl(
		base, underlying, -1, ssl, state, options);
	return bev;

err:
	if (options & BEV_OPT_CLOSE_ON_FREE)
		SSL_free(ssl);
	return NULL;
}