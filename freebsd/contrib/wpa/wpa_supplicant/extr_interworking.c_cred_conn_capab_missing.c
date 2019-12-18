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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int dummy; } ;
struct wpa_cred {unsigned int num_req_conn_capab; int** req_conn_capab_port; int /*<<< orphan*/ * req_conn_capab_proto; } ;
struct wpa_bss {TYPE_1__* anqp; } ;
struct TYPE_2__ {int /*<<< orphan*/ * hs20_connection_capability; int /*<<< orphan*/ * domain_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  has_proto_match (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_proto_port_match (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int interworking_home_sp_cred (struct wpa_supplicant*,struct wpa_cred*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpabuf_head (int /*<<< orphan*/ *) ; 
 int wpabuf_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cred_conn_capab_missing(struct wpa_supplicant *wpa_s,
				   struct wpa_cred *cred, struct wpa_bss *bss)
{
#ifdef CONFIG_HS20
	int res;
	const u8 *capab, *end;
	unsigned int i, j;
	int *ports;

	if (!cred->num_req_conn_capab)
		return 0; /* No connection capability constraint specified */

	if (bss->anqp == NULL || bss->anqp->hs20_connection_capability == NULL)
		return 0; /* No Connection Capability known - ignore constraint
			   */

	res = interworking_home_sp_cred(wpa_s, cred, bss->anqp ?
					bss->anqp->domain_name : NULL);
	if (res > 0)
		return 0; /* No constraint in home network */

	capab = wpabuf_head(bss->anqp->hs20_connection_capability);
	end = capab + wpabuf_len(bss->anqp->hs20_connection_capability);

	for (i = 0; i < cred->num_req_conn_capab; i++) {
		ports = cred->req_conn_capab_port[i];
		if (!ports) {
			if (!has_proto_match(capab, end,
					     cred->req_conn_capab_proto[i]))
				return 1;
		} else {
			for (j = 0; ports[j] > -1; j++) {
				if (!has_proto_port_match(
					    capab, end,
					    cred->req_conn_capab_proto[i],
					    ports[j]))
					return 1;
			}
		}
	}
#endif /* CONFIG_HS20 */

	return 0;
}