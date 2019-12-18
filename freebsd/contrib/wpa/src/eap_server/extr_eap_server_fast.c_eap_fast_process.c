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
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_fast_data {int /*<<< orphan*/  ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_FAST ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  eap_fast_process_msg ; 
 int /*<<< orphan*/  eap_fast_process_version ; 
 int /*<<< orphan*/  eap_fast_state (struct eap_fast_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_server_tls_process (struct eap_sm*,int /*<<< orphan*/ *,struct wpabuf*,struct eap_fast_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_fast_process(struct eap_sm *sm, void *priv,
			     struct wpabuf *respData)
{
	struct eap_fast_data *data = priv;
	if (eap_server_tls_process(sm, &data->ssl, respData, data,
				   EAP_TYPE_FAST, eap_fast_process_version,
				   eap_fast_process_msg) < 0)
		eap_fast_state(data, FAILURE);
}