#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* rpc_t ;
typedef  int /*<<< orphan*/  rpc_status ;
typedef  int /*<<< orphan*/  plist_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* on_error ) (TYPE_1__*,char*,char const*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_ERROR ; 
 int /*<<< orphan*/  RPC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  rpc_args_to_xml (TYPE_1__*,int /*<<< orphan*/  const,char**,int) ; 
 int /*<<< orphan*/  rpc_recv_applicationConnected (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  rpc_recv_applicationDisconnected (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  rpc_recv_applicationSentData (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  rpc_recv_applicationSentListing (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  rpc_recv_applicationUpdated (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  rpc_recv_reportConnectedApplicationList (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  rpc_recv_reportSetup (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,char const*,char*) ; 

rpc_status rpc_recv_msg(rpc_t self, const char *selector, const plist_t args) {
  if (!selector) {
    return RPC_ERROR;
  }

  if (!strcmp(selector, "_rpc_reportSetup:")) {
    if (!rpc_recv_reportSetup(self, args)) {
      return RPC_SUCCESS;
    }
  } else if (!strcmp(selector, "_rpc_reportConnectedApplicationList:")) {
    if (!rpc_recv_reportConnectedApplicationList(self, args)) {
      return RPC_SUCCESS;
    }
  } else if (!strcmp(selector, "_rpc_applicationConnected:")) {
    if (!rpc_recv_applicationConnected(self, args)) {
      return RPC_SUCCESS;
    }
  } else if (!strcmp(selector, "_rpc_applicationDisconnected:")) {
    if (!rpc_recv_applicationDisconnected(self, args)) {
      return RPC_SUCCESS;
    }
  } else if (!strcmp(selector, "_rpc_applicationSentListing:")) {
    if (!rpc_recv_applicationSentListing(self, args)) {
      return RPC_SUCCESS;
    }
  } else if (!strcmp(selector, "_rpc_applicationSentData:")) {
    if (!rpc_recv_applicationSentData(self, args)) {
      return RPC_SUCCESS;
    }
  } else if (!strcmp(selector, "_rpc_applicationUpdated:")) {
    if (!rpc_recv_applicationUpdated(self, args)) {
      return RPC_SUCCESS;
    }
  } else if (!strcmp(selector, "_rpc_reportConnectedDriverList:")) {
    return RPC_SUCCESS;
  }

  // invalid msg
  char *args_xml = NULL;
  rpc_args_to_xml(self, args, &args_xml, true);
  rpc_status ret = self->on_error(self, "Invalid message %s %s",
      selector, args_xml);
  free(args_xml);
  return ret;
}