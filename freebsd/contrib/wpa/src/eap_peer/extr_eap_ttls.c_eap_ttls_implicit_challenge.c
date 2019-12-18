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
struct eap_ttls_data {int /*<<< orphan*/  ssl; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * eap_peer_tls_derive_key (struct eap_sm*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static u8 * eap_ttls_implicit_challenge(struct eap_sm *sm,
					struct eap_ttls_data *data, size_t len)
{
	return eap_peer_tls_derive_key(sm, &data->ssl, "ttls challenge",
				       NULL, 0, len);
}