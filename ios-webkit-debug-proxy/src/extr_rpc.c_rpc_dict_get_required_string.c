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
typedef  int /*<<< orphan*/  rpc_status ;
typedef  int /*<<< orphan*/  plist_t ;

/* Variables and functions */
 scalar_t__ PLIST_STRING ; 
 int /*<<< orphan*/  RPC_ERROR ; 
 int /*<<< orphan*/  RPC_SUCCESS ; 
 int /*<<< orphan*/  plist_dict_get_item (int /*<<< orphan*/  const,char const*) ; 
 scalar_t__ plist_get_node_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plist_get_string_val (int /*<<< orphan*/ ,char**) ; 

rpc_status rpc_dict_get_required_string(const plist_t node, const char *key,
    char **to_value) {
  if (!node || !key || !to_value) {
    return RPC_ERROR;
  }
  plist_t item = plist_dict_get_item(node, key);
  if (plist_get_node_type(item) != PLIST_STRING) {
    return RPC_ERROR;
  }
  plist_get_string_val(item, to_value);
  return RPC_SUCCESS;
}