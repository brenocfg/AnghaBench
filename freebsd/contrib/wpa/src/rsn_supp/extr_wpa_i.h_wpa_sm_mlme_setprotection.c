#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_sm {TYPE_1__* ctx; } ;
struct TYPE_2__ {int (* mlme_setprotection ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int) ;int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_ASSERT (int (*) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int)) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static inline int wpa_sm_mlme_setprotection(struct wpa_sm *sm, const u8 *addr,
					    int protect_type, int key_type)
{
	WPA_ASSERT(sm->ctx->mlme_setprotection);
	return sm->ctx->mlme_setprotection(sm->ctx->ctx, addr, protect_type,
					   key_type);
}