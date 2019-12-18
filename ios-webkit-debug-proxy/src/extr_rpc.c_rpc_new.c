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
struct rpc_struct {int dummy; } ;
typedef  TYPE_1__* rpc_t ;
struct TYPE_4__ {int /*<<< orphan*/  on_error; int /*<<< orphan*/  recv_plist; int /*<<< orphan*/  send_forwardDidClose; int /*<<< orphan*/  send_forwardSocketData; int /*<<< orphan*/  send_forwardSocketSetup; int /*<<< orphan*/  send_forwardIndicateWebView; int /*<<< orphan*/  send_forwardGetListing; int /*<<< orphan*/  send_getConnectedApplications; int /*<<< orphan*/  send_reportIdentifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rpc_on_error ; 
 int /*<<< orphan*/  rpc_recv_plist ; 
 int /*<<< orphan*/  rpc_send_forwardDidClose ; 
 int /*<<< orphan*/  rpc_send_forwardGetListing ; 
 int /*<<< orphan*/  rpc_send_forwardIndicateWebView ; 
 int /*<<< orphan*/  rpc_send_forwardSocketData ; 
 int /*<<< orphan*/  rpc_send_forwardSocketSetup ; 
 int /*<<< orphan*/  rpc_send_getConnectedApplications ; 
 int /*<<< orphan*/  rpc_send_reportIdentifier ; 

rpc_t rpc_new() {
  rpc_t self = (rpc_t)malloc(sizeof(struct rpc_struct));
  if (!self) {
    return NULL;
  }
  memset(self, 0, sizeof(struct rpc_struct));
  self->send_reportIdentifier = rpc_send_reportIdentifier;
  self->send_getConnectedApplications = rpc_send_getConnectedApplications;
  self->send_forwardGetListing = rpc_send_forwardGetListing;
  self->send_forwardIndicateWebView = rpc_send_forwardIndicateWebView;
  self->send_forwardSocketSetup = rpc_send_forwardSocketSetup;
  self->send_forwardSocketData = rpc_send_forwardSocketData;
  self->send_forwardDidClose = rpc_send_forwardDidClose;
  self->recv_plist = rpc_recv_plist;
  self->on_error = rpc_on_error;
  return self;
}