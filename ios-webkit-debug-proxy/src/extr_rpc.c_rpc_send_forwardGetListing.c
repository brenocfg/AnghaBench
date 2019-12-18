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
typedef  int /*<<< orphan*/  rpc_t ;
typedef  int /*<<< orphan*/  rpc_status ;
typedef  int /*<<< orphan*/  plist_t ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_ERROR ; 
 int /*<<< orphan*/  plist_dict_set_item (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plist_new_string (char const*) ; 
 int /*<<< orphan*/  rpc_new_args (char const*) ; 
 int /*<<< orphan*/  rpc_send_msg (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

rpc_status rpc_send_forwardGetListing(rpc_t self, const char *connection_id,
    const char *app_id) {
  if (!connection_id || !app_id) {
    return RPC_ERROR;
  }
  const char *selector = "_rpc_forwardGetListing:";
  plist_t args = rpc_new_args(connection_id);
  plist_dict_set_item(args, "WIRApplicationIdentifierKey",
      plist_new_string(app_id));
  rpc_status ret = rpc_send_msg(self, selector, args);
  plist_free(args);
  return ret;
}