#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  task; int /*<<< orphan*/  running; int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ isc_httpdmgr_t ;
struct TYPE_9__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_2__ isc_httpd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER (char*) ; 
 int /*<<< orphan*/  EXIT (char*) ; 
 TYPE_2__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_2__* ISC_LIST_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_SOCKCANCEL_ALL ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSETSHUTTINGDOWN (TYPE_1__*) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_socket_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 

void
isc_httpdmgr_shutdown(isc_httpdmgr_t **httpdmgrp)
{
	isc_httpdmgr_t *httpdmgr;
	isc_httpd_t *httpd;
	httpdmgr = *httpdmgrp;
	*httpdmgrp = NULL;

	ENTER("isc_httpdmgr_shutdown");

	LOCK(&httpdmgr->lock);

	MSETSHUTTINGDOWN(httpdmgr);

	isc_socket_cancel(httpdmgr->sock, httpdmgr->task, ISC_SOCKCANCEL_ALL);

	httpd = ISC_LIST_HEAD(httpdmgr->running);
	while (httpd != NULL) {
		isc_socket_cancel(httpd->sock, httpdmgr->task,
				  ISC_SOCKCANCEL_ALL);
		httpd = ISC_LIST_NEXT(httpd, link);
	}

	UNLOCK(&httpdmgr->lock);

	EXIT("isc_httpdmgr_shutdown");
}