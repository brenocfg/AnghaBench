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
typedef  int /*<<< orphan*/  UInt32 ;
struct TYPE_3__ {int /*<<< orphan*/  btNumAvailBytes; } ;
typedef  TYPE_1__ CMatchFinderMt ;

/* Variables and functions */
 int /*<<< orphan*/  GET_NEXT_BLOCK_IF_REQUIRED ; 

__attribute__((used)) static UInt32 MatchFinderMt_GetNumAvailableBytes(CMatchFinderMt *p)
{
  GET_NEXT_BLOCK_IF_REQUIRED;
  return p->btNumAvailBytes;
}