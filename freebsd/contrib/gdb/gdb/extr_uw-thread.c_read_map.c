#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread_map {int dummy; } ;
struct TYPE_3__ {int (* to_xfer_memory ) (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ THR_MAP (int /*<<< orphan*/ ) ; 
 TYPE_1__ base_ops ; 
 int stub1 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
read_map (CORE_ADDR mapp, struct thread_map *map)
{
  return base_ops.to_xfer_memory ((CORE_ADDR)THR_MAP (mapp), (char *)map,
				  sizeof (*map), 0, NULL, &base_ops);
}