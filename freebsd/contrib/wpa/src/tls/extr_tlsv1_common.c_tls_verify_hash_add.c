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
typedef  int /*<<< orphan*/  u8 ;
struct tls_verify_hash {scalar_t__ sha256_cert; scalar_t__ sha256_server; scalar_t__ sha256_client; scalar_t__ sha1_cert; scalar_t__ md5_cert; scalar_t__ sha1_server; scalar_t__ md5_server; scalar_t__ sha1_client; scalar_t__ md5_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_hash_update (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 

void tls_verify_hash_add(struct tls_verify_hash *verify, const u8 *buf,
			 size_t len)
{
	if (verify->md5_client && verify->sha1_client) {
		crypto_hash_update(verify->md5_client, buf, len);
		crypto_hash_update(verify->sha1_client, buf, len);
	}
	if (verify->md5_server && verify->sha1_server) {
		crypto_hash_update(verify->md5_server, buf, len);
		crypto_hash_update(verify->sha1_server, buf, len);
	}
	if (verify->md5_cert && verify->sha1_cert) {
		crypto_hash_update(verify->md5_cert, buf, len);
		crypto_hash_update(verify->sha1_cert, buf, len);
	}
#ifdef CONFIG_TLSV12
	if (verify->sha256_client)
		crypto_hash_update(verify->sha256_client, buf, len);
	if (verify->sha256_server)
		crypto_hash_update(verify->sha256_server, buf, len);
	if (verify->sha256_cert)
		crypto_hash_update(verify->sha256_cert, buf, len);
#endif /* CONFIG_TLSV12 */
}