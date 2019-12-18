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
struct eap_tls_data {int /*<<< orphan*/  ssl; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int eap_peer_tls_status (struct eap_sm*,int /*<<< orphan*/ *,char*,size_t,int) ; 

__attribute__((used)) static int eap_tls_get_status(struct eap_sm *sm, void *priv, char *buf,
			      size_t buflen, int verbose)
{
	struct eap_tls_data *data = priv;
	return eap_peer_tls_status(sm, &data->ssl, buf, buflen, verbose);
}