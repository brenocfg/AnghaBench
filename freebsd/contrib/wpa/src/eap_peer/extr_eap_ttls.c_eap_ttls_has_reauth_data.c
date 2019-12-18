#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_ttls_data {scalar_t__ phase2_success; TYPE_1__ ssl; } ;
struct eap_sm {int /*<<< orphan*/  ssl_ctx; } ;
typedef  int Boolean ;

/* Variables and functions */
 scalar_t__ tls_connection_established (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Boolean eap_ttls_has_reauth_data(struct eap_sm *sm, void *priv)
{
	struct eap_ttls_data *data = priv;
	return tls_connection_established(sm->ssl_ctx, data->ssl.conn) &&
		data->phase2_success;
}