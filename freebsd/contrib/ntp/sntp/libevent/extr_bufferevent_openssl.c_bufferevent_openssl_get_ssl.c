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
struct bufferevent_openssl {int /*<<< orphan*/ * ssl; } ;
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 struct bufferevent_openssl* upcast (struct bufferevent*) ; 

SSL *
bufferevent_openssl_get_ssl(struct bufferevent *bufev)
{
	struct bufferevent_openssl *bev_ssl = upcast(bufev);
	if (!bev_ssl)
		return NULL;
	return bev_ssl->ssl;
}