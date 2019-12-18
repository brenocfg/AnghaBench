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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_8__ {void* action_arg; int /*<<< orphan*/ * action; int /*<<< orphan*/ * url; } ;
typedef  TYPE_1__ isc_httpdurl_t ;
struct TYPE_9__ {int /*<<< orphan*/  urls; int /*<<< orphan*/  mctx; int /*<<< orphan*/ * render_404; } ;
typedef  TYPE_2__ isc_httpdmgr_t ;
typedef  int /*<<< orphan*/  isc_httpdaction_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_LINK_INIT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_APPEND (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_NOMEMORY ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 TYPE_1__* isc_mem_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * isc_mem_strdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  link ; 

isc_result_t
isc_httpdmgr_addurl(isc_httpdmgr_t *httpdmgr, const char *url,
		    isc_httpdaction_t *func, void *arg)
{
	isc_httpdurl_t *item;

	if (url == NULL) {
		httpdmgr->render_404 = func;
		return (ISC_R_SUCCESS);
	}

	item = isc_mem_get(httpdmgr->mctx, sizeof(isc_httpdurl_t));
	if (item == NULL)
		return (ISC_R_NOMEMORY);

	item->url = isc_mem_strdup(httpdmgr->mctx, url);
	if (item->url == NULL) {
		isc_mem_put(httpdmgr->mctx, item, sizeof(isc_httpdurl_t));
		return (ISC_R_NOMEMORY);
	}

	item->action = func;
	item->action_arg = arg;
	ISC_LINK_INIT(item, link);
	ISC_LIST_APPEND(httpdmgr->urls, item, link);

	return (ISC_R_SUCCESS);
}