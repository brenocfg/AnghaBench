#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpc_page_struct {int dummy; } ;
typedef  TYPE_1__* rpc_page_t ;
struct TYPE_5__ {struct TYPE_5__* url; struct TYPE_5__* title; struct TYPE_5__* connection_id; scalar_t__ page_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void rpc_free_page(rpc_page_t page) {
  if (page) {
    page->page_id = 0;
    free(page->connection_id);
    free(page->title);
    free(page->url);
    memset(page, 0, sizeof(struct rpc_page_struct));
    free(page);
  }
}