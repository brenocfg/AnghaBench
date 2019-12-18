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
typedef  scalar_t__ rpc_page_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  rpc_free_page (int /*<<< orphan*/ ) ; 

void rpc_free_pages(rpc_page_t *pages) {
  if (pages) {
    rpc_page_t *p = pages;
    while (*p) {
      rpc_free_page(*p++);
    }
    free(pages);
  }
}