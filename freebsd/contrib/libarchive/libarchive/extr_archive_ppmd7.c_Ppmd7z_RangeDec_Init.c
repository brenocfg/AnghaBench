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
struct TYPE_6__ {TYPE_1__* Stream; } ;
struct TYPE_5__ {scalar_t__ (* Read ) (void*) ;} ;
typedef  TYPE_2__ CPpmd7z_RangeDec ;
typedef  int /*<<< orphan*/  Bool ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  Ppmd_RangeDec_Init (TYPE_2__*) ; 
 scalar_t__ stub1 (void*) ; 

__attribute__((used)) static Bool Ppmd7z_RangeDec_Init(CPpmd7z_RangeDec *p)
{
  if (p->Stream->Read((void *)p->Stream) != 0)
    return False;
  return Ppmd_RangeDec_Init(p);
}