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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  rpc_status ;
typedef  int /*<<< orphan*/  plist_t ;

/* Variables and functions */
 scalar_t__ PLIST_DATA ; 
 int /*<<< orphan*/  RPC_ERROR ; 
 int /*<<< orphan*/  RPC_SUCCESS ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  plist_dict_get_item (int /*<<< orphan*/  const,char const*) ; 
 int /*<<< orphan*/  plist_get_data_val (int /*<<< orphan*/ ,char**,scalar_t__*) ; 
 scalar_t__ plist_get_node_type (int /*<<< orphan*/ ) ; 

rpc_status rpc_dict_get_required_data(const plist_t node, const char *key,
    char **to_value, size_t *to_length) {
  if (!node || !key || !to_value || !to_length) {
    return RPC_ERROR;
  }
  *to_value = NULL;
  *to_length = 0;
  plist_t item = plist_dict_get_item(node, key);
  if (plist_get_node_type(item) != PLIST_DATA) {
    return RPC_ERROR;
  }
  char *data = NULL;
  uint64_t length = 0;
  plist_get_data_val(item, &data, &length);
  if (length > UINT32_MAX) {
    free(data);
    return RPC_ERROR;
  }
  *to_value = data;
  *to_length = (size_t)length;
  return RPC_SUCCESS;
}