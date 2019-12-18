#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  mctx; int /*<<< orphan*/  running; } ;
typedef  TYPE_1__ isc_httpdmgr_t ;
struct TYPE_8__ {scalar_t__ headerlen; struct TYPE_8__* headerdata; int /*<<< orphan*/  sock; TYPE_1__* mgr; } ;
typedef  TYPE_2__ isc_httpd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_LIST_UNLINK (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpdmgr_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  isc_socket_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
destroy_client(isc_httpd_t **httpdp)
{
	isc_httpd_t *httpd = *httpdp;
	isc_httpdmgr_t *httpdmgr = httpd->mgr;

	*httpdp = NULL;

	LOCK(&httpdmgr->lock);

	isc_socket_detach(&httpd->sock);
	ISC_LIST_UNLINK(httpdmgr->running, httpd, link);

	if (httpd->headerlen > 0)
		isc_mem_put(httpdmgr->mctx, httpd->headerdata,
			    httpd->headerlen);

	isc_mem_put(httpdmgr->mctx, httpd, sizeof(isc_httpd_t));

	UNLOCK(&httpdmgr->lock);

	httpdmgr_destroy(httpdmgr);
}