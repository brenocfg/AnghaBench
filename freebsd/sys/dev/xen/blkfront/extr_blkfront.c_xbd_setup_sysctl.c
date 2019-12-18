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
struct xbd_softc {int /*<<< orphan*/  xbd_ring_pages; int /*<<< orphan*/  xbd_max_request_size; int /*<<< orphan*/  xbd_max_request_segments; int /*<<< orphan*/  xbd_max_requests; int /*<<< orphan*/  xbd_dev; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct xbd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbd_sysctl_features ; 

__attribute__((used)) static void
xbd_setup_sysctl(struct xbd_softc *xbd)
{
	struct sysctl_ctx_list *sysctl_ctx = NULL;
	struct sysctl_oid *sysctl_tree = NULL;
	struct sysctl_oid_list *children;
	
	sysctl_ctx = device_get_sysctl_ctx(xbd->xbd_dev);
	if (sysctl_ctx == NULL)
		return;

	sysctl_tree = device_get_sysctl_tree(xbd->xbd_dev);
	if (sysctl_tree == NULL)
		return;

	children = SYSCTL_CHILDREN(sysctl_tree);
	SYSCTL_ADD_UINT(sysctl_ctx, children, OID_AUTO,
	    "max_requests", CTLFLAG_RD, &xbd->xbd_max_requests, -1,
	    "maximum outstanding requests (negotiated)");

	SYSCTL_ADD_UINT(sysctl_ctx, children, OID_AUTO,
	    "max_request_segments", CTLFLAG_RD,
	    &xbd->xbd_max_request_segments, 0,
	    "maximum number of pages per requests (negotiated)");

	SYSCTL_ADD_UINT(sysctl_ctx, children, OID_AUTO,
	    "max_request_size", CTLFLAG_RD, &xbd->xbd_max_request_size, 0,
	    "maximum size in bytes of a request (negotiated)");

	SYSCTL_ADD_UINT(sysctl_ctx, children, OID_AUTO,
	    "ring_pages", CTLFLAG_RD, &xbd->xbd_ring_pages, 0,
	    "communication channel pages (negotiated)");

	SYSCTL_ADD_PROC(sysctl_ctx, children, OID_AUTO,
	    "features", CTLTYPE_STRING|CTLFLAG_RD, xbd, 0,
	    xbd_sysctl_features, "A", "protocol features (negotiated)");
}