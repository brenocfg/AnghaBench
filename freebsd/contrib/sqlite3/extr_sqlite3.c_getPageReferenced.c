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
struct TYPE_3__ {int nPage; int* aPgRef; } ;
typedef  int Pgno ;
typedef  TYPE_1__ IntegrityCk ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int getPageReferenced(IntegrityCk *pCheck, Pgno iPg){
  assert( iPg<=pCheck->nPage && sizeof(pCheck->aPgRef[0])==1 );
  return (pCheck->aPgRef[iPg/8] & (1 << (iPg & 0x07)));
}