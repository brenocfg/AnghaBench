#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* filters; scalar_t__ unpackSize; scalar_t__ packSize; scalar_t__ flags; } ;
struct TYPE_7__ {scalar_t__ propsSize; int /*<<< orphan*/  props; scalar_t__ id; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISeqOutStream ;
typedef  TYPE_1__ CXzFilter ;
typedef  TYPE_2__ CXzBlock ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 int /*<<< orphan*/  CrcCalc (scalar_t__*,unsigned int) ; 
 int /*<<< orphan*/  SetUi32 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBytes (int /*<<< orphan*/ *,scalar_t__*,unsigned int) ; 
 int XZ_BLOCK_HEADER_SIZE_MAX ; 
 unsigned int XzBlock_GetNumFilters (TYPE_2__ const*) ; 
 scalar_t__ XzBlock_HasPackSize (TYPE_2__ const*) ; 
 scalar_t__ XzBlock_HasUnpackSize (TYPE_2__ const*) ; 
 scalar_t__ Xz_WriteVarInt (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static SRes XzBlock_WriteHeader(const CXzBlock *p, ISeqOutStream *s)
{
  Byte header[XZ_BLOCK_HEADER_SIZE_MAX];

  unsigned pos = 1;
  unsigned numFilters, i;
  header[pos++] = p->flags;

  if (XzBlock_HasPackSize(p)) pos += Xz_WriteVarInt(header + pos, p->packSize);
  if (XzBlock_HasUnpackSize(p)) pos += Xz_WriteVarInt(header + pos, p->unpackSize);
  numFilters = XzBlock_GetNumFilters(p);
  
  for (i = 0; i < numFilters; i++)
  {
    const CXzFilter *f = &p->filters[i];
    pos += Xz_WriteVarInt(header + pos, f->id);
    pos += Xz_WriteVarInt(header + pos, f->propsSize);
    memcpy(header + pos, f->props, f->propsSize);
    pos += f->propsSize;
  }

  while ((pos & 3) != 0)
    header[pos++] = 0;

  header[0] = (Byte)(pos >> 2);
  SetUi32(header + pos, CrcCalc(header, pos));
  return WriteBytes(s, header, pos + 4);
}