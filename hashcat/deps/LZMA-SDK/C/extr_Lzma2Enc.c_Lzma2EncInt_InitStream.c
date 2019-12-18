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
struct TYPE_6__ {scalar_t__ propsAreSet; int /*<<< orphan*/  propsByte; int /*<<< orphan*/  enc; } ;
struct TYPE_5__ {int /*<<< orphan*/  lzmaProps; } ;
typedef  int SizeT ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CLzma2EncProps ;
typedef  TYPE_2__ CLzma2EncInt ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int LZMA_PROPS_SIZE ; 
 int /*<<< orphan*/  LzmaEnc_SetProps (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LzmaEnc_WriteProperties (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_OK ; 
 scalar_t__ True ; 

__attribute__((used)) static SRes Lzma2EncInt_InitStream(CLzma2EncInt *p, const CLzma2EncProps *props)
{
  if (!p->propsAreSet)
  {
    SizeT propsSize = LZMA_PROPS_SIZE;
    Byte propsEncoded[LZMA_PROPS_SIZE];
    RINOK(LzmaEnc_SetProps(p->enc, &props->lzmaProps));
    RINOK(LzmaEnc_WriteProperties(p->enc, propsEncoded, &propsSize));
    p->propsByte = propsEncoded[0];
    p->propsAreSet = True;
  }
  return SZ_OK;
}