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
struct p2p_srv_bonjour {int /*<<< orphan*/  resp; int /*<<< orphan*/  query; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct p2p_srv_bonjour*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpas_p2p_srv_bonjour_free(struct p2p_srv_bonjour *bsrv)
{
	dl_list_del(&bsrv->list);
	wpabuf_free(bsrv->query);
	wpabuf_free(bsrv->resp);
	os_free(bsrv);
}