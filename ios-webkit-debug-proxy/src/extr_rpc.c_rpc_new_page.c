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
struct rpc_page_struct {int dummy; } ;
typedef  scalar_t__ rpc_page_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

rpc_page_t rpc_new_page() {
  rpc_page_t page = (rpc_page_t)malloc(sizeof(struct rpc_page_struct));
  if (page) {
    memset(page, 0, sizeof(struct rpc_page_struct));
  }
  return page;
}