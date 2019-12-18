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
typedef  int /*<<< orphan*/  uint8_t ;
struct hmac_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_eli_crypto_hmac_final (struct hmac_ctx*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  g_eli_crypto_hmac_init (struct hmac_ctx*,char const*,size_t) ; 
 int /*<<< orphan*/  g_eli_crypto_hmac_update (struct hmac_ctx*,int /*<<< orphan*/  const*,size_t) ; 

void
g_eli_crypto_hmac(const char *hkey, size_t hkeysize, const uint8_t *data,
    size_t datasize, uint8_t *md, size_t mdsize)
{
	struct hmac_ctx ctx;

	g_eli_crypto_hmac_init(&ctx, hkey, hkeysize);
	g_eli_crypto_hmac_update(&ctx, data, datasize);
	g_eli_crypto_hmac_final(&ctx, md, mdsize);
}