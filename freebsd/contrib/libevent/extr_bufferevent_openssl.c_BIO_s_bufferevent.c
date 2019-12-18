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
typedef  int /*<<< orphan*/  BIO_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_TYPE_LIBEVENT ; 
 int /*<<< orphan*/ * BIO_meth_new (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_meth_set_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_bufferevent_ctrl ; 
 int /*<<< orphan*/  bio_bufferevent_free ; 
 int /*<<< orphan*/  bio_bufferevent_new ; 
 int /*<<< orphan*/  bio_bufferevent_puts ; 
 int /*<<< orphan*/  bio_bufferevent_read ; 
 int /*<<< orphan*/  bio_bufferevent_write ; 
 int /*<<< orphan*/ * methods_bufferevent ; 

__attribute__((used)) static BIO_METHOD *
BIO_s_bufferevent(void)
{
	if (methods_bufferevent == NULL) {
		methods_bufferevent = BIO_meth_new(BIO_TYPE_LIBEVENT, "bufferevent");
		if (methods_bufferevent == NULL)
			return NULL;
		BIO_meth_set_write(methods_bufferevent, bio_bufferevent_write);
		BIO_meth_set_read(methods_bufferevent, bio_bufferevent_read);
		BIO_meth_set_puts(methods_bufferevent, bio_bufferevent_puts);
		BIO_meth_set_ctrl(methods_bufferevent, bio_bufferevent_ctrl);
		BIO_meth_set_create(methods_bufferevent, bio_bufferevent_new);
		BIO_meth_set_destroy(methods_bufferevent, bio_bufferevent_free);
	}
	return methods_bufferevent;
}