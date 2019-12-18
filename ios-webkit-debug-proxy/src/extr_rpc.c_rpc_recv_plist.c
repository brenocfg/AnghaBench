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
 int /*<<< orphan*/  plist_dict_get_item (int /*<<< orphan*/  const,char*) ; 
 int /*<<< orphan*/  plist_get_string_val (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  rpc_recv_msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

rpc_status rpc_recv_plist(rpc_t self, const plist_t rpc_dict) {
  char *selector = NULL;
  plist_get_string_val(plist_dict_get_item(rpc_dict, "__selector"), &selector);
  plist_t args = plist_dict_get_item(rpc_dict, "__argument");
  return rpc_recv_msg(self, selector, args);
}