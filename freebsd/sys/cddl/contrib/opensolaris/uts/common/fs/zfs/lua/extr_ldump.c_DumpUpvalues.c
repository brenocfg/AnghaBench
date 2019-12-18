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
struct TYPE_5__ {int sizeupvalues; TYPE_1__* upvalues; } ;
struct TYPE_4__ {int /*<<< orphan*/  idx; int /*<<< orphan*/  instack; } ;
typedef  TYPE_2__ Proto ;
typedef  int /*<<< orphan*/  DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  DumpChar (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpInt (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DumpUpvalues(const Proto* f, DumpState* D)
{
 int i,n=f->sizeupvalues;
 DumpInt(n,D);
 for (i=0; i<n; i++)
 {
  DumpChar(f->upvalues[i].instack,D);
  DumpChar(f->upvalues[i].idx,D);
 }
}