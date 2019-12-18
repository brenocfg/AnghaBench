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
typedef  int /*<<< orphan*/  plist_t ;

/* Variables and functions */
 int /*<<< orphan*/  plist_dict_set_item (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plist_new_dict () ; 
 int /*<<< orphan*/  plist_new_string (char const*) ; 

plist_t rpc_new_args(const char *connection_id) {
  plist_t ret = plist_new_dict();
  if (connection_id) {
    plist_dict_set_item(ret, "WIRConnectionIdentifierKey",
        plist_new_string(connection_id));
  }
  return ret;
}