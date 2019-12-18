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
struct gather_data {int dummy; } ;

/* Variables and functions */
 int memcache_return_file_location (struct gather_data*) ; 
 scalar_t__ rpc_mode (struct gather_data*) ; 
 int rpc_return_file_location (struct gather_data*) ; 

__attribute__((used)) static int return_file_location (struct gather_data *G) {
  return rpc_mode (G) ? rpc_return_file_location (G) : memcache_return_file_location (G);
}