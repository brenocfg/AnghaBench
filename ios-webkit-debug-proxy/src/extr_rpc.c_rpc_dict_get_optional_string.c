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
 int /*<<< orphan*/  RPC_ERROR ; 
 int /*<<< orphan*/  RPC_SUCCESS ; 
 scalar_t__ plist_dict_get_item (int /*<<< orphan*/  const,char const*) ; 
 int /*<<< orphan*/  rpc_dict_get_required_string (int /*<<< orphan*/  const,char const*,char**) ; 

rpc_status rpc_dict_get_optional_string(const plist_t node, const char *key,
    char **to_value) {
  if (!node || !key || !to_value) {
    return RPC_ERROR;
  }
  return (plist_dict_get_item(node, key) ?
      rpc_dict_get_required_string(node, key, to_value) : RPC_SUCCESS);
}