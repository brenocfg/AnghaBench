#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt64 ;
typedef  scalar_t__ UInt32 ;
struct TYPE_22__ {scalar_t__ Defs; } ;
struct TYPE_18__ {scalar_t__ Data; scalar_t__ Size; } ;
struct TYPE_17__ {scalar_t__ Data; scalar_t__ Size; } ;
struct TYPE_16__ {scalar_t__ Data; scalar_t__ Size; } ;
struct TYPE_21__ {TYPE_3__ sdCRCs; TYPE_2__ sdSizes; scalar_t__ NumSubDigests; scalar_t__ NumTotalSubStreams; TYPE_1__ sdNumSubStreams; } ;
struct TYPE_20__ {scalar_t__ NumFolders; TYPE_8__ FolderCRCs; } ;
struct TYPE_19__ {scalar_t__ Data; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_4__ CSzData ;
typedef  TYPE_5__ CSzAr ;
typedef  TYPE_6__ CSubStreamInfo ;

/* Variables and functions */
 scalar_t__ CountDefinedBits (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadID (TYPE_4__*,scalar_t__*) ; 
 int /*<<< orphan*/  SZ_ERROR_UNSUPPORTED ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  SkipBitUi32s (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  SkipData (TYPE_4__*) ; 
 int /*<<< orphan*/  SkipNumbers (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  SzBitWithVals_Check (TYPE_8__*,scalar_t__) ; 
 int /*<<< orphan*/  SzReadNumber32 (TYPE_4__*,scalar_t__*) ; 
 scalar_t__ k7zIdCRC ; 
 scalar_t__ k7zIdEnd ; 
 scalar_t__ k7zIdNumUnpackStream ; 
 scalar_t__ k7zIdSize ; 

__attribute__((used)) static SRes ReadSubStreamsInfo(CSzAr *p, CSzData *sd, CSubStreamInfo *ssi)
{
  UInt64 type = 0;
  UInt32 numSubDigests = 0;
  UInt32 numFolders = p->NumFolders;
  UInt32 numUnpackStreams = numFolders;
  UInt32 numUnpackSizesInData = 0;

  for (;;)
  {
    RINOK(ReadID(sd, &type));
    if (type == k7zIdNumUnpackStream)
    {
      UInt32 i;
      ssi->sdNumSubStreams.Data = sd->Data;
      numUnpackStreams = 0;
      numSubDigests = 0;
      for (i = 0; i < numFolders; i++)
      {
        UInt32 numStreams;
        RINOK(SzReadNumber32(sd, &numStreams));
        if (numUnpackStreams > numUnpackStreams + numStreams)
          return SZ_ERROR_UNSUPPORTED;
        numUnpackStreams += numStreams;
        if (numStreams != 0)
          numUnpackSizesInData += (numStreams - 1);
        if (numStreams != 1 || !SzBitWithVals_Check(&p->FolderCRCs, i))
          numSubDigests += numStreams;
      }
      ssi->sdNumSubStreams.Size = sd->Data - ssi->sdNumSubStreams.Data;
      continue;
    }
    if (type == k7zIdCRC || type == k7zIdSize || type == k7zIdEnd)
      break;
    RINOK(SkipData(sd));
  }

  if (!ssi->sdNumSubStreams.Data)
  {
    numSubDigests = numFolders;
    if (p->FolderCRCs.Defs)
      numSubDigests = numFolders - CountDefinedBits(p->FolderCRCs.Defs, numFolders);
  }
  
  ssi->NumTotalSubStreams = numUnpackStreams;
  ssi->NumSubDigests = numSubDigests;

  if (type == k7zIdSize)
  {
    ssi->sdSizes.Data = sd->Data;
    RINOK(SkipNumbers(sd, numUnpackSizesInData));
    ssi->sdSizes.Size = sd->Data - ssi->sdSizes.Data;
    RINOK(ReadID(sd, &type));
  }

  for (;;)
  {
    if (type == k7zIdEnd)
      return SZ_OK;
    if (type == k7zIdCRC)
    {
      ssi->sdCRCs.Data = sd->Data;
      RINOK(SkipBitUi32s(sd, numSubDigests));
      ssi->sdCRCs.Size = sd->Data - ssi->sdCRCs.Data;
    }
    else
    {
      RINOK(SkipData(sd));
    }
    RINOK(ReadID(sd, &type));
  }
}