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
struct eap_ttls_data {int ttls_version; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static int eap_ttls_process_version(struct eap_sm *sm, void *priv,
				    int peer_version)
{
	struct eap_ttls_data *data = priv;
	if (peer_version < data->ttls_version) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS: peer ver=%d, own ver=%d; "
			   "use version %d",
			   peer_version, data->ttls_version, peer_version);
		data->ttls_version = peer_version;
	}

	return 0;
}