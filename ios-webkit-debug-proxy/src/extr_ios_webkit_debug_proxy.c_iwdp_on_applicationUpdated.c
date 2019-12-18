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

/* Variables and functions */
 int /*<<< orphan*/  iwdp_add_app_id (int /*<<< orphan*/ ,char const*) ; 

rpc_status iwdp_on_applicationUpdated(rpc_t rpc,
    const char *app_id, const char *dest_id) {
  return iwdp_add_app_id(rpc, dest_id);
}