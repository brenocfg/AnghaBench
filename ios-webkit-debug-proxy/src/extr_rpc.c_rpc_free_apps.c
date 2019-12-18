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
typedef  scalar_t__ rpc_app_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  rpc_free_app (int /*<<< orphan*/ ) ; 

void rpc_free_apps(rpc_app_t *apps) {
  if (apps) {
    rpc_app_t *a = apps;
    while (*a) {
      rpc_free_app(*a++);
    }
    free(apps);
  }
}