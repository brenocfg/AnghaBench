#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  id ;
typedef  int UInt64 ;
typedef  scalar_t__ UInt32 ;
struct TYPE_11__ {scalar_t__ InIndex; scalar_t__ OutIndex; } ;
struct TYPE_10__ {int NumStreams; int PropsOffset; int PropsSize; scalar_t__ MethodID; } ;
struct TYPE_9__ {int* Data; unsigned int Size; } ;
struct TYPE_8__ {scalar_t__ NumCoders; scalar_t__* PackStreams; scalar_t__ UnpackStream; TYPE_4__* Bonds; scalar_t__ NumPackStreams; scalar_t__ NumBonds; TYPE_3__* Coders; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CSzFolder ;
typedef  TYPE_2__ CSzData ;
typedef  TYPE_3__ CSzCoderInfo ;
typedef  TYPE_4__ CSzBond ;
typedef  int Byte ;

/* Variables and functions */
 int False ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_ARCHIVE ; 
 int /*<<< orphan*/  SZ_ERROR_UNSUPPORTED ; 
 scalar_t__ SZ_NUM_BONDS_IN_FOLDER_MAX ; 
 scalar_t__ SZ_NUM_CODERS_IN_FOLDER_MAX ; 
 scalar_t__ SZ_NUM_PACK_STREAMS_IN_FOLDER_MAX ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  SZ_READ_BYTE (int) ; 
 int /*<<< orphan*/  SzReadNumber32 (TYPE_2__*,scalar_t__*) ; 
 int True ; 
 scalar_t__ k_NumCodersStreams_in_Folder_MAX ; 

SRes SzGetNextFolderItem(CSzFolder *f, CSzData *sd)
{
  UInt32 numCoders, i;
  UInt32 numInStreams = 0;
  const Byte *dataStart = sd->Data;

  f->NumCoders = 0;
  f->NumBonds = 0;
  f->NumPackStreams = 0;
  f->UnpackStream = 0;
  
  RINOK(SzReadNumber32(sd, &numCoders));
  if (numCoders == 0 || numCoders > SZ_NUM_CODERS_IN_FOLDER_MAX)
    return SZ_ERROR_UNSUPPORTED;
  
  for (i = 0; i < numCoders; i++)
  {
    Byte mainByte;
    CSzCoderInfo *coder = f->Coders + i;
    unsigned idSize, j;
    UInt64 id;
    
    SZ_READ_BYTE(mainByte);
    if ((mainByte & 0xC0) != 0)
      return SZ_ERROR_UNSUPPORTED;
    
    idSize = (unsigned)(mainByte & 0xF);
    if (idSize > sizeof(id))
      return SZ_ERROR_UNSUPPORTED;
    if (idSize > sd->Size)
      return SZ_ERROR_ARCHIVE;
    id = 0;
    for (j = 0; j < idSize; j++)
    {
      id = ((id << 8) | *sd->Data);
      sd->Data++;
      sd->Size--;
    }
    if (id > (UInt32)0xFFFFFFFF)
      return SZ_ERROR_UNSUPPORTED;
    coder->MethodID = (UInt32)id;
    
    coder->NumStreams = 1;
    coder->PropsOffset = 0;
    coder->PropsSize = 0;
    
    if ((mainByte & 0x10) != 0)
    {
      UInt32 numStreams;
      
      RINOK(SzReadNumber32(sd, &numStreams));
      if (numStreams > k_NumCodersStreams_in_Folder_MAX)
        return SZ_ERROR_UNSUPPORTED;
      coder->NumStreams = (Byte)numStreams;

      RINOK(SzReadNumber32(sd, &numStreams));
      if (numStreams != 1)
        return SZ_ERROR_UNSUPPORTED;
    }

    numInStreams += coder->NumStreams;

    if (numInStreams > k_NumCodersStreams_in_Folder_MAX)
      return SZ_ERROR_UNSUPPORTED;

    if ((mainByte & 0x20) != 0)
    {
      UInt32 propsSize = 0;
      RINOK(SzReadNumber32(sd, &propsSize));
      if (propsSize > sd->Size)
        return SZ_ERROR_ARCHIVE;
      if (propsSize >= 0x80)
        return SZ_ERROR_UNSUPPORTED;
      coder->PropsOffset = sd->Data - dataStart;
      coder->PropsSize = (Byte)propsSize;
      sd->Data += (size_t)propsSize;
      sd->Size -= (size_t)propsSize;
    }
  }

  /*
  if (numInStreams == 1 && numCoders == 1)
  {
    f->NumPackStreams = 1;
    f->PackStreams[0] = 0;
  }
  else
  */
  {
    Byte streamUsed[k_NumCodersStreams_in_Folder_MAX];
    UInt32 numBonds, numPackStreams;
    
    numBonds = numCoders - 1;
    if (numInStreams < numBonds)
      return SZ_ERROR_ARCHIVE;
    if (numBonds > SZ_NUM_BONDS_IN_FOLDER_MAX)
      return SZ_ERROR_UNSUPPORTED;
    f->NumBonds = numBonds;
    
    numPackStreams = numInStreams - numBonds;
    if (numPackStreams > SZ_NUM_PACK_STREAMS_IN_FOLDER_MAX)
      return SZ_ERROR_UNSUPPORTED;
    f->NumPackStreams = numPackStreams;
  
    for (i = 0; i < numInStreams; i++)
      streamUsed[i] = False;
    
    if (numBonds != 0)
    {
      Byte coderUsed[SZ_NUM_CODERS_IN_FOLDER_MAX];

      for (i = 0; i < numCoders; i++)
        coderUsed[i] = False;
      
      for (i = 0; i < numBonds; i++)
      {
        CSzBond *bp = f->Bonds + i;
        
        RINOK(SzReadNumber32(sd, &bp->InIndex));
        if (bp->InIndex >= numInStreams || streamUsed[bp->InIndex])
          return SZ_ERROR_ARCHIVE;
        streamUsed[bp->InIndex] = True;
        
        RINOK(SzReadNumber32(sd, &bp->OutIndex));
        if (bp->OutIndex >= numCoders || coderUsed[bp->OutIndex])
          return SZ_ERROR_ARCHIVE;
        coderUsed[bp->OutIndex] = True;
      }
      
      for (i = 0; i < numCoders; i++)
        if (!coderUsed[i])
        {
          f->UnpackStream = i;
          break;
        }
      
      if (i == numCoders)
        return SZ_ERROR_ARCHIVE;
    }
    
    if (numPackStreams == 1)
    {
      for (i = 0; i < numInStreams; i++)
        if (!streamUsed[i])
          break;
      if (i == numInStreams)
        return SZ_ERROR_ARCHIVE;
      f->PackStreams[0] = i;
    }
    else
      for (i = 0; i < numPackStreams; i++)
      {
        UInt32 index;
        RINOK(SzReadNumber32(sd, &index));
        if (index >= numInStreams || streamUsed[index])
          return SZ_ERROR_ARCHIVE;
        streamUsed[index] = True;
        f->PackStreams[i] = index;
      }
  }

  f->NumCoders = numCoders;

  return SZ_OK;
}