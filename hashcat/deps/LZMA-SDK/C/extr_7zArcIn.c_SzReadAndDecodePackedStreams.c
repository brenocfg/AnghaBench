#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UInt64 ;
typedef  scalar_t__ UInt32 ;
struct TYPE_11__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {scalar_t__ NumFolders; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  int /*<<< orphan*/  ILookInStream ;
typedef  int /*<<< orphan*/  CSzData ;
typedef  TYPE_1__ CSzAr ;
typedef  int /*<<< orphan*/  CSubStreamInfo ;
typedef  TYPE_2__ CBuf ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_Create (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Buf_Init (TYPE_2__*) ; 
 int /*<<< orphan*/  LookInStream_SeekTo (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_ARCHIVE ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  SzAr_DecodeFolder (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t SzAr_GetFolderUnpackSize (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  SzReadStreamsInfo (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SRes SzReadAndDecodePackedStreams(
    ILookInStream *inStream,
    CSzData *sd,
    CBuf *tempBufs,
    UInt32 numFoldersMax,
    UInt64 baseOffset,
    CSzAr *p,
    ISzAllocPtr allocTemp)
{
  UInt64 dataStartPos;
  UInt32 fo;
  CSubStreamInfo ssi;

  RINOK(SzReadStreamsInfo(p, sd, numFoldersMax, NULL, 0, &dataStartPos, &ssi, allocTemp));
  
  dataStartPos += baseOffset;
  if (p->NumFolders == 0)
    return SZ_ERROR_ARCHIVE;
 
  for (fo = 0; fo < p->NumFolders; fo++)
    Buf_Init(tempBufs + fo);
  
  for (fo = 0; fo < p->NumFolders; fo++)
  {
    CBuf *tempBuf = tempBufs + fo;
    UInt64 unpackSize = SzAr_GetFolderUnpackSize(p, fo);
    if ((size_t)unpackSize != unpackSize)
      return SZ_ERROR_MEM;
    if (!Buf_Create(tempBuf, (size_t)unpackSize, allocTemp))
      return SZ_ERROR_MEM;
  }
  
  for (fo = 0; fo < p->NumFolders; fo++)
  {
    const CBuf *tempBuf = tempBufs + fo;
    RINOK(LookInStream_SeekTo(inStream, dataStartPos));
    RINOK(SzAr_DecodeFolder(p, fo, inStream, dataStartPos, tempBuf->data, tempBuf->size, allocTemp));
  }
  
  return SZ_OK;
}