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
typedef  int UInt32 ;
struct TYPE_6__ {int pb; int lc; int lp; } ;
struct TYPE_7__ {TYPE_1__ prop; int /*<<< orphan*/  dicPos; } ;
struct TYPE_8__ {int state; int control; int needInitLevel; int unpackSize; int packSize; TYPE_2__ decoder; int /*<<< orphan*/  isExtraMode; } ;
typedef  int ELzma2State ;
typedef  TYPE_3__ CLzma2Dec ;
typedef  int Byte ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int LZMA2_CONTROL_COPY_RESET_DIC ; 
 int /*<<< orphan*/  LZMA2_IS_UNCOMPRESSED_STATE (TYPE_3__*) ; 
 unsigned int LZMA2_LCLP_MAX ; 
#define  LZMA2_STATE_CONTROL 133 
 int LZMA2_STATE_DATA ; 
 int LZMA2_STATE_ERROR ; 
 int LZMA2_STATE_FINISHED ; 
#define  LZMA2_STATE_PACK0 132 
#define  LZMA2_STATE_PACK1 131 
#define  LZMA2_STATE_PROP 130 
#define  LZMA2_STATE_UNPACK0 129 
#define  LZMA2_STATE_UNPACK1 128 
 int /*<<< orphan*/  PRF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 

__attribute__((used)) static ELzma2State Lzma2Dec_UpdateState(CLzma2Dec *p, Byte b)
{
  switch (p->state)
  {
    case LZMA2_STATE_CONTROL:
      p->isExtraMode = False;
      p->control = b;
      PRF(printf("\n %8X", (unsigned)p->decoder.dicPos));
      PRF(printf(" %02X", (unsigned)b));
      if (b == 0)
        return LZMA2_STATE_FINISHED;
      if (LZMA2_IS_UNCOMPRESSED_STATE(p))
      {
        if (b == LZMA2_CONTROL_COPY_RESET_DIC)
          p->needInitLevel = 0xC0;
        else if (b > 2 || p->needInitLevel == 0xE0)
          return LZMA2_STATE_ERROR;
      }
      else
      {
        if (b < p->needInitLevel)
          return LZMA2_STATE_ERROR;
        p->needInitLevel = 0;
        p->unpackSize = (UInt32)(b & 0x1F) << 16;
      }
      return LZMA2_STATE_UNPACK0;
    
    case LZMA2_STATE_UNPACK0:
      p->unpackSize |= (UInt32)b << 8;
      return LZMA2_STATE_UNPACK1;
    
    case LZMA2_STATE_UNPACK1:
      p->unpackSize |= (UInt32)b;
      p->unpackSize++;
      PRF(printf(" %7u", (unsigned)p->unpackSize));
      return LZMA2_IS_UNCOMPRESSED_STATE(p) ? LZMA2_STATE_DATA : LZMA2_STATE_PACK0;
    
    case LZMA2_STATE_PACK0:
      p->packSize = (UInt32)b << 8;
      return LZMA2_STATE_PACK1;

    case LZMA2_STATE_PACK1:
      p->packSize |= (UInt32)b;
      p->packSize++;
      // if (p->packSize < 5) return LZMA2_STATE_ERROR;
      PRF(printf(" %5u", (unsigned)p->packSize));
      return (p->control & 0x40) ? LZMA2_STATE_PROP : LZMA2_STATE_DATA;

    case LZMA2_STATE_PROP:
    {
      unsigned lc, lp;
      if (b >= (9 * 5 * 5))
        return LZMA2_STATE_ERROR;
      lc = b % 9;
      b /= 9;
      p->decoder.prop.pb = (Byte)(b / 5);
      lp = b % 5;
      if (lc + lp > LZMA2_LCLP_MAX)
        return LZMA2_STATE_ERROR;
      p->decoder.prop.lc = (Byte)lc;
      p->decoder.prop.lp = (Byte)lp;
      return LZMA2_STATE_DATA;
    }
  }
  return LZMA2_STATE_ERROR;
}