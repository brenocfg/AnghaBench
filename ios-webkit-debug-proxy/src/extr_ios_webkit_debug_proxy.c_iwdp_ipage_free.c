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
struct iwdp_ipage_struct {int dummy; } ;
typedef  TYPE_1__* iwdp_ipage_t ;
struct TYPE_5__ {struct TYPE_5__* sender_id; struct TYPE_5__* url; struct TYPE_5__* title; struct TYPE_5__* connection_id; struct TYPE_5__* app_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void iwdp_ipage_free(iwdp_ipage_t ipage) {
  if (ipage) {
    free(ipage->app_id);
    free(ipage->connection_id);
    free(ipage->title);
    free(ipage->url);
    free(ipage->sender_id);
    memset(ipage, 0, sizeof(struct iwdp_ipage_struct));
    free(ipage);
  }
}