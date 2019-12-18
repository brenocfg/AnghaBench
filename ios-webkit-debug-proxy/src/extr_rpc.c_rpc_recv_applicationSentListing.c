#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* rpc_t ;
typedef  int /*<<< orphan*/  rpc_status ;
typedef  int /*<<< orphan*/  rpc_page_t ;
typedef  int /*<<< orphan*/  plist_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* on_applicationSentListing ) (TYPE_1__*,char*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_ERROR ; 
 int /*<<< orphan*/  RPC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  plist_dict_get_item (int /*<<< orphan*/  const,char*) ; 
 int /*<<< orphan*/  rpc_dict_get_required_string (int /*<<< orphan*/  const,char*,char**) ; 
 int /*<<< orphan*/  rpc_free_pages (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_parse_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 

rpc_status rpc_recv_applicationSentListing(rpc_t self, const plist_t args) {
  char *app_id = NULL;
  rpc_page_t *pages = NULL;
  plist_t item = plist_dict_get_item(args, "WIRListingKey");
  rpc_status ret;
  if (!rpc_dict_get_required_string(args, "WIRApplicationIdentifierKey",
        &app_id) &&
      !rpc_parse_pages(item, &pages) &&
      !self->on_applicationSentListing(self, app_id, pages)) {
    ret = RPC_SUCCESS;
  } else {
    ret = RPC_ERROR;
  }
  free(app_id);
  rpc_free_pages(pages);
  return ret;
}