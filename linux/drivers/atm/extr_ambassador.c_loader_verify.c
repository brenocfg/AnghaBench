#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  count; int /*<<< orphan*/  address; } ;
typedef  TYPE_2__ transfer_block ;
struct ihex_binrec {int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_2__ transfer; } ;
struct TYPE_8__ {TYPE_1__ payload; } ;
typedef  TYPE_3__ loader_block ;
typedef  int /*<<< orphan*/  amb_dev ;

/* Variables and functions */
 int DBG_FLOW ; 
 int DBG_LOAD ; 
 int EINVAL ; 
 int /*<<< orphan*/  PRINTD (int,char*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int do_loader_command (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_adapter_memory ; 

__attribute__((used)) static int loader_verify(loader_block *lb, const amb_dev *dev,
			 const struct ihex_binrec *rec)
{
  transfer_block * tb = &lb->payload.transfer;
  int res;
  
  PRINTD (DBG_FLOW|DBG_LOAD, "loader_verify");
  
  tb->address = rec->addr;
  tb->count = cpu_to_be32(be16_to_cpu(rec->len) / 4);
  res = do_loader_command (lb, dev, read_adapter_memory);
  if (!res && memcmp(tb->data, rec->data, be16_to_cpu(rec->len)))
    res = -EINVAL;
  return res;
}