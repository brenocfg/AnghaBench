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
struct TYPE_3__ {int Code; int Range; int /*<<< orphan*/  Stream; } ;
typedef  TYPE_1__ CPpmd7z_RangeDec ;
typedef  int BoolInt ;

/* Variables and functions */
 int False ; 
 int IByteIn_Read (int /*<<< orphan*/ ) ; 

BoolInt Ppmd7z_RangeDec_Init(CPpmd7z_RangeDec *p)
{
  unsigned i;
  p->Code = 0;
  p->Range = 0xFFFFFFFF;
  if (IByteIn_Read(p->Stream) != 0)
    return False;
  for (i = 0; i < 4; i++)
    p->Code = (p->Code << 8) | IByteIn_Read(p->Stream);
  return (p->Code < 0xFFFFFFFF);
}