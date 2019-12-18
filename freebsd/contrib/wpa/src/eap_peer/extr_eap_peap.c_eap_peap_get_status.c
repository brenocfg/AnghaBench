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
struct eap_sm {int dummy; } ;
struct eap_peap_data {TYPE_1__* phase2_method; int /*<<< orphan*/  peap_version; int /*<<< orphan*/  ssl; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int eap_peer_tls_status (struct eap_sm*,int /*<<< orphan*/ *,char*,size_t,int) ; 
 int os_snprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 

__attribute__((used)) static int eap_peap_get_status(struct eap_sm *sm, void *priv, char *buf,
			       size_t buflen, int verbose)
{
	struct eap_peap_data *data = priv;
	int len, ret;

	len = eap_peer_tls_status(sm, &data->ssl, buf, buflen, verbose);
	if (data->phase2_method) {
		ret = os_snprintf(buf + len, buflen - len,
				  "EAP-PEAPv%d Phase2 method=%s\n",
				  data->peap_version,
				  data->phase2_method->name);
		if (os_snprintf_error(buflen - len, ret))
			return len;
		len += ret;
	}
	return len;
}