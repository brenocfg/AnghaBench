#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_mem_t ;
struct TYPE_9__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_1__ isc_httpdurl_t ;
struct TYPE_10__ {int /*<<< orphan*/ * mctx; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* ondestroy ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  urls; int /*<<< orphan*/ * timermgr; int /*<<< orphan*/  task; int /*<<< orphan*/  sock; int /*<<< orphan*/  running; } ;
typedef  TYPE_2__ isc_httpdmgr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER (char*) ; 
 int /*<<< orphan*/  EXIT (char*) ; 
 int /*<<< orphan*/  ISC_LIST_EMPTY (int /*<<< orphan*/ ) ; 
 TYPE_1__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_UNLINK (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSHUTTINGDOWN (TYPE_2__*) ; 
 int /*<<< orphan*/  NOTICE (char*) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_mem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  isc_mem_putanddetach (int /*<<< orphan*/ **,TYPE_2__*,int) ; 
 int /*<<< orphan*/  isc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_socket_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_task_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
httpdmgr_destroy(isc_httpdmgr_t *httpdmgr)
{
	isc_mem_t *mctx;
	isc_httpdurl_t *url;

	ENTER("httpdmgr_destroy");

	LOCK(&httpdmgr->lock);

	if (!MSHUTTINGDOWN(httpdmgr)) {
		NOTICE("httpdmgr_destroy not shutting down yet");
		UNLOCK(&httpdmgr->lock);
		return;
	}

	/*
	 * If all clients are not shut down, don't do anything yet.
	 */
	if (!ISC_LIST_EMPTY(httpdmgr->running)) {
		NOTICE("httpdmgr_destroy clients still active");
		UNLOCK(&httpdmgr->lock);
		return;
	}

	NOTICE("httpdmgr_destroy detaching socket, task, and timermgr");

	isc_socket_detach(&httpdmgr->sock);
	isc_task_detach(&httpdmgr->task);
	httpdmgr->timermgr = NULL;

	/*
	 * Clear out the list of all actions we know about.  Just free the
	 * memory.
	 */
	url = ISC_LIST_HEAD(httpdmgr->urls);
	while (url != NULL) {
		isc_mem_free(httpdmgr->mctx, url->url);
		ISC_LIST_UNLINK(httpdmgr->urls, url, link);
		isc_mem_put(httpdmgr->mctx, url, sizeof(isc_httpdurl_t));
		url = ISC_LIST_HEAD(httpdmgr->urls);
	}

	UNLOCK(&httpdmgr->lock);
	(void)isc_mutex_destroy(&httpdmgr->lock);

	if (httpdmgr->ondestroy != NULL)
		(httpdmgr->ondestroy)(httpdmgr->cb_arg);

	mctx = httpdmgr->mctx;
	isc_mem_putanddetach(&mctx, httpdmgr, sizeof(isc_httpdmgr_t));

	EXIT("httpdmgr_destroy");
}