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
struct wpabuf {int dummy; } ;
struct p2p_group {scalar_t__ wfd_ie; TYPE_1__* p2p; scalar_t__ members; int /*<<< orphan*/  noa; } ;
struct TYPE_2__ {scalar_t__* vendor_elem; } ;

/* Variables and functions */
 size_t VENDOR_ELEM_PROBE_RESP_P2P_GO ; 
 int /*<<< orphan*/  p2p_buf_add_device_info (struct wpabuf*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_buf_add_group_info (struct p2p_group*,struct wpabuf*,int) ; 
 int /*<<< orphan*/  p2p_group_add_common_ies (struct p2p_group*,struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_group_add_noa (struct wpabuf*,int /*<<< orphan*/ ) ; 
 struct wpabuf* p2p_group_encaps_probe_resp (struct wpabuf*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 struct wpabuf* wpabuf_concat (struct wpabuf*,struct wpabuf*) ; 
 struct wpabuf* wpabuf_dup (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static struct wpabuf * p2p_group_build_probe_resp_ie(struct p2p_group *group)
{
	struct wpabuf *p2p_subelems, *ie;

	p2p_subelems = wpabuf_alloc(500);
	if (p2p_subelems == NULL)
		return NULL;

	p2p_group_add_common_ies(group, p2p_subelems);
	p2p_group_add_noa(p2p_subelems, group->noa);

	/* P2P Device Info */
	p2p_buf_add_device_info(p2p_subelems, group->p2p, NULL);

	/* P2P Group Info: Only when at least one P2P Client is connected */
	if (group->members)
		p2p_buf_add_group_info(group, p2p_subelems, -1);

	ie = p2p_group_encaps_probe_resp(p2p_subelems);
	wpabuf_free(p2p_subelems);

	if (group->p2p->vendor_elem &&
	    group->p2p->vendor_elem[VENDOR_ELEM_PROBE_RESP_P2P_GO]) {
		struct wpabuf *extra;
		extra = wpabuf_dup(group->p2p->vendor_elem[VENDOR_ELEM_PROBE_RESP_P2P_GO]);
		ie = wpabuf_concat(extra, ie);
	}

#ifdef CONFIG_WIFI_DISPLAY
	if (group->wfd_ie) {
		struct wpabuf *wfd = wpabuf_dup(group->wfd_ie);
		ie = wpabuf_concat(wfd, ie);
	}
#endif /* CONFIG_WIFI_DISPLAY */

	return ie;
}