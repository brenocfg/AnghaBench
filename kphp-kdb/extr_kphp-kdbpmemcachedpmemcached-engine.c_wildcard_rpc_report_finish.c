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

/* Variables and functions */
 int /*<<< orphan*/  tl_store_raw_data (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wildcard_add_rpc_value (char const*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ wildcard_ptr ; 
 int /*<<< orphan*/  wildcard_total_data_sent ; 
 int wildcard_total_keys_sent ; 

void wildcard_rpc_report_finish (const char *key, int key_len) {
  *(int *)wildcard_ptr = wildcard_total_keys_sent;
  wildcard_add_rpc_value (key, key_len, wildcard_ptr, wildcard_total_data_sent);
  tl_store_raw_data (wildcard_ptr, wildcard_total_data_sent);
}