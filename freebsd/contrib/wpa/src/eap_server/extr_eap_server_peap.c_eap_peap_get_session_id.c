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
struct eap_sm {int dummy; } ;
struct eap_peap_data {scalar_t__ state; int /*<<< orphan*/  ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_PEAP ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/ * eap_server_tls_derive_session_id (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static u8 * eap_peap_get_session_id(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_peap_data *data = priv;

	if (data->state != SUCCESS)
		return NULL;

	return eap_server_tls_derive_session_id(sm, &data->ssl, EAP_TYPE_PEAP,
						len);
}