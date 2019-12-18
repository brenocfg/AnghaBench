#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * Stamps; scalar_t__* FreeList; } ;
struct TYPE_4__ {int /*<<< orphan*/  NU; scalar_t__ Next; int /*<<< orphan*/  Stamp; } ;
typedef  scalar_t__ CPpmd8_Node_Ref ;
typedef  TYPE_1__ CPpmd8_Node ;
typedef  TYPE_2__ CPpmd8 ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_NODE ; 
 int /*<<< orphan*/  I2U (unsigned int) ; 
 scalar_t__ REF (void*) ; 

__attribute__((used)) static void InsertNode(CPpmd8 *p, void *node, unsigned indx)
{
  ((CPpmd8_Node *)node)->Stamp = EMPTY_NODE;
  ((CPpmd8_Node *)node)->Next = (CPpmd8_Node_Ref)p->FreeList[indx];
  ((CPpmd8_Node *)node)->NU = I2U(indx);
  p->FreeList[indx] = REF(node);
  p->Stamps[indx]++;
}