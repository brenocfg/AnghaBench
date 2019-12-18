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
struct rpc_app_struct {int dummy; } ;
typedef  scalar_t__ rpc_app_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

rpc_app_t rpc_new_app() {
  rpc_app_t app = (rpc_app_t)malloc(sizeof(struct rpc_app_struct));
  if (app) {
    memset(app, 0, sizeof(struct rpc_app_struct));
  }
  return app;
}