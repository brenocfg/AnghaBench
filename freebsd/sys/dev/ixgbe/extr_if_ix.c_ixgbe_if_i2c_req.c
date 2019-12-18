#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* read_i2c_byte ) (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
struct ifi2creq {int len; int /*<<< orphan*/ * data; int /*<<< orphan*/  dev_addr; scalar_t__ offset; } ;
struct adapter {struct ixgbe_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int ENXIO ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ixgbe_if_i2c_req(if_ctx_t ctx, struct ifi2creq *req)
{
	struct adapter		*adapter = iflib_get_softc(ctx);
	struct ixgbe_hw 	*hw = &adapter->hw;
	int 			i;


	if (hw->phy.ops.read_i2c_byte == NULL)
		return (ENXIO);
	for (i = 0; i < req->len; i++)
		hw->phy.ops.read_i2c_byte(hw, req->offset + i,
		    req->dev_addr, &req->data[i]);
	return (0);
}