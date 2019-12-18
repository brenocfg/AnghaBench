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
struct tls_connection {int /*<<< orphan*/ * engine; int /*<<< orphan*/ * private_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void tls_engine_deinit(struct tls_connection *conn)
{
#if defined(ANDROID) || !defined(OPENSSL_NO_ENGINE)
	wpa_printf(MSG_DEBUG, "ENGINE: engine deinit");
	if (conn->private_key) {
		EVP_PKEY_free(conn->private_key);
		conn->private_key = NULL;
	}
	if (conn->engine) {
#if !defined(OPENSSL_IS_BORINGSSL)
		ENGINE_finish(conn->engine);
#endif /* !OPENSSL_IS_BORINGSSL */
		conn->engine = NULL;
	}
#endif /* ANDROID || !OPENSSL_NO_ENGINE */
}