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
struct drbd_connection {int /*<<< orphan*/ * int_dig_vv; int /*<<< orphan*/ * int_dig_in; int /*<<< orphan*/ * peer_integrity_tfm; int /*<<< orphan*/ * integrity_tfm; int /*<<< orphan*/ * cram_hmac_tfm; int /*<<< orphan*/ * verify_tfm; int /*<<< orphan*/ * csums_tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_free_sock (struct drbd_connection*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void conn_free_crypto(struct drbd_connection *connection)
{
	drbd_free_sock(connection);

	crypto_free_shash(connection->csums_tfm);
	crypto_free_shash(connection->verify_tfm);
	crypto_free_shash(connection->cram_hmac_tfm);
	crypto_free_shash(connection->integrity_tfm);
	crypto_free_shash(connection->peer_integrity_tfm);
	kfree(connection->int_dig_in);
	kfree(connection->int_dig_vv);

	connection->csums_tfm = NULL;
	connection->verify_tfm = NULL;
	connection->cram_hmac_tfm = NULL;
	connection->integrity_tfm = NULL;
	connection->peer_integrity_tfm = NULL;
	connection->int_dig_in = NULL;
	connection->int_dig_vv = NULL;
}