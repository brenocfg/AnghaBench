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
struct testcase_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ ) ; 
 int basic_test_cleanup (struct testcase_t const*,void*) ; 
 int /*<<< orphan*/ * exit_base ; 
 scalar_t__ got_close ; 
 scalar_t__ got_error ; 
 scalar_t__ got_timeout ; 
 scalar_t__ n_connected ; 
 scalar_t__ pending_connect_events ; 
 int renegotiate_at ; 
 scalar_t__ stop_when_connected ; 
 scalar_t__ test_is_done ; 
 int /*<<< orphan*/  the_cert ; 
 int /*<<< orphan*/  the_key ; 
 int /*<<< orphan*/ * the_ssl_ctx ; 

__attribute__((used)) static int
ssl_test_cleanup(const struct testcase_t *testcase, void *ptr)
{
	int ret = basic_test_cleanup(testcase, ptr);
	if (!ret) {
		return ret;
	}

	test_is_done = 0;
	n_connected = 0;
	got_close = 0;
	got_error = 0;
	got_timeout = 0;
	renegotiate_at = -1;
	stop_when_connected = 0;
	pending_connect_events = 0;
	exit_base = NULL;

	X509_free(the_cert);
	EVP_PKEY_free(the_key);

	SSL_CTX_free(the_ssl_ctx);
	the_ssl_ctx = NULL;

	return 1;
}