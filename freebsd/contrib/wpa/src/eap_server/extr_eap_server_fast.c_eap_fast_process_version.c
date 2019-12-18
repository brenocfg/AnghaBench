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
struct eap_sm {int dummy; } ;
struct eap_fast_data {int peer_version; int force_version; int fast_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int,...) ; 

__attribute__((used)) static int eap_fast_process_version(struct eap_sm *sm, void *priv,
				    int peer_version)
{
	struct eap_fast_data *data = priv;

	data->peer_version = peer_version;

	if (data->force_version >= 0 && peer_version != data->force_version) {
		wpa_printf(MSG_INFO, "EAP-FAST: peer did not select the forced"
			   " version (forced=%d peer=%d) - reject",
			   data->force_version, peer_version);
		return -1;
	}

	if (peer_version < data->fast_version) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: peer ver=%d, own ver=%d; "
			   "use version %d",
			   peer_version, data->fast_version, peer_version);
		data->fast_version = peer_version;
	}

	return 0;
}