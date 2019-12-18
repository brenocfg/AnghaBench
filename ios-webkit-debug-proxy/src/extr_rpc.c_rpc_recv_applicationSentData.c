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
typedef  int /*<<< orphan*/  plist_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* on_applicationSentData ) (TYPE_1__*,char*,char*,char*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_ERROR ; 
 int /*<<< orphan*/  RPC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  rpc_dict_get_required_data (int /*<<< orphan*/  const,char*,char**,size_t*) ; 
 int /*<<< orphan*/  rpc_dict_get_required_string (int /*<<< orphan*/  const,char*,char**) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,char*,char*,size_t) ; 

rpc_status rpc_recv_applicationSentData(rpc_t self, const plist_t args) {
  char *app_id = NULL;
  char *dest_id = NULL;
  char *data = NULL;
  size_t length = 0;
  rpc_status ret;
  if (!rpc_dict_get_required_string(args, "WIRApplicationIdentifierKey",
        &app_id) &&
      !rpc_dict_get_required_string(args, "WIRDestinationKey",
        &dest_id) &&
      !rpc_dict_get_required_data(args, "WIRMessageDataKey",
        &data, &length) &&
      !self->on_applicationSentData(self,
        app_id, dest_id, data, length)) {
    ret = RPC_SUCCESS;
  } else {
    ret = RPC_ERROR;
  }
  free(app_id);
  free(dest_id);
  free(data);
  return ret;
}