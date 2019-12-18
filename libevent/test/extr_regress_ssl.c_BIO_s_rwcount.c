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
 int /*<<< orphan*/  BIO_TYPE_LIBEVENT_RWCOUNT ; 
 int /*<<< orphan*/ * BIO_meth_new (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_meth_set_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_rwcount_ctrl ; 
 int /*<<< orphan*/  bio_rwcount_free ; 
 int /*<<< orphan*/  bio_rwcount_new ; 
 int /*<<< orphan*/  bio_rwcount_puts ; 
 int /*<<< orphan*/  bio_rwcount_read ; 
 int /*<<< orphan*/  bio_rwcount_write ; 
 int /*<<< orphan*/ * methods_rwcount ; 

__attribute__((used)) static BIO_METHOD *
BIO_s_rwcount(void)
{
	if (methods_rwcount == NULL) {
		methods_rwcount = BIO_meth_new(BIO_TYPE_LIBEVENT_RWCOUNT, "rwcount");
		if (methods_rwcount == NULL)
			return NULL;
		BIO_meth_set_write(methods_rwcount, bio_rwcount_write);
		BIO_meth_set_read(methods_rwcount, bio_rwcount_read);
		BIO_meth_set_puts(methods_rwcount, bio_rwcount_puts);
		BIO_meth_set_ctrl(methods_rwcount, bio_rwcount_ctrl);
		BIO_meth_set_create(methods_rwcount, bio_rwcount_new);
		BIO_meth_set_destroy(methods_rwcount, bio_rwcount_free);
	}
	return methods_rwcount;
}