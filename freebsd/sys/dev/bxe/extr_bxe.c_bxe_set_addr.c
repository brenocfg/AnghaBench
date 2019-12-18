#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;
struct ecore_vlan_mac_obj {int dummy; } ;
struct bxe_set_addr_ctx {int rc; TYPE_2__* sc; int /*<<< orphan*/  ramrod_flags; } ;
struct TYPE_6__ {TYPE_1__* sp_objs; } ;
struct TYPE_5__ {struct ecore_vlan_mac_obj mac_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BLOGE (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  DBG_SP ; 
 int /*<<< orphan*/  ECORE_UC_LIST_MAC ; 
 int EEXIST ; 
 scalar_t__ LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  TRUE ; 
 int bxe_set_mac_one (TYPE_2__*,int /*<<< orphan*/ *,struct ecore_vlan_mac_obj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_int
bxe_set_addr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
    struct bxe_set_addr_ctx *ctx = arg;
    struct ecore_vlan_mac_obj *mac_obj = &ctx->sc->sp_objs->mac_obj;
    int rc;

    if (ctx->rc < 0)
	return (0);

    rc = bxe_set_mac_one(ctx->sc, (uint8_t *)LLADDR(sdl), mac_obj, TRUE,
                         ECORE_UC_LIST_MAC, &ctx->ramrod_flags);

    /* do not treat adding same MAC as an error */
    if (rc == -EEXIST)
	BLOGD(ctx->sc, DBG_SP, "Failed to schedule ADD operations (EEXIST)\n");
    else if (rc < 0) {
            BLOGE(ctx->sc, "Failed to schedule ADD operations (%d)\n", rc);
            ctx->rc = rc;
    }

    return (1);
}