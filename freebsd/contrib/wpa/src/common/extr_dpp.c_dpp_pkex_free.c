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
struct dpp_pkex {int /*<<< orphan*/  exchange_resp; int /*<<< orphan*/  exchange_req; int /*<<< orphan*/  peer_bootstrap_key; int /*<<< orphan*/  y; int /*<<< orphan*/  x; struct dpp_pkex* code; struct dpp_pkex* identifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct dpp_pkex*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void dpp_pkex_free(struct dpp_pkex *pkex)
{
	if (!pkex)
		return;

	os_free(pkex->identifier);
	os_free(pkex->code);
	EVP_PKEY_free(pkex->x);
	EVP_PKEY_free(pkex->y);
	EVP_PKEY_free(pkex->peer_bootstrap_key);
	wpabuf_free(pkex->exchange_req);
	wpabuf_free(pkex->exchange_resp);
	os_free(pkex);
}