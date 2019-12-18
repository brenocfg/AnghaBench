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
struct iwdp_iws_struct {int dummy; } ;
typedef  TYPE_1__* iwdp_iws_t ;
struct TYPE_5__ {struct TYPE_5__* ws_id; int /*<<< orphan*/  ws; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ws_free (int /*<<< orphan*/ ) ; 

void iwdp_iws_free(iwdp_iws_t iws) {
  if (iws) {
    ws_free(iws->ws);
    free(iws->ws_id);
    memset(iws, 0, sizeof(struct iwdp_iws_struct));
    free(iws);
  }
}