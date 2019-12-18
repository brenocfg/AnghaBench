#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt64 ;
typedef  int /*<<< orphan*/  UInt32 ;
struct TYPE_10__ {int /*<<< orphan*/  NumTotalSubStreams; int /*<<< orphan*/  sdNumSubStreams; int /*<<< orphan*/  sdCRCs; int /*<<< orphan*/  sdSizes; } ;
struct TYPE_9__ {int /*<<< orphan*/  NumFolders; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  int /*<<< orphan*/  CSzData ;
typedef  TYPE_1__ CSzAr ;
typedef  TYPE_2__ CSubStreamInfo ;
typedef  int /*<<< orphan*/  CBuf ;

/* Variables and functions */
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadID (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ReadNumber (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ReadPackInfo (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadSubStreamsInfo (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ReadUnpackInfo (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_UNSUPPORTED ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  SzData_Clear (int /*<<< orphan*/ *) ; 
 scalar_t__ k7zIdEnd ; 
 scalar_t__ k7zIdPackInfo ; 
 scalar_t__ k7zIdSubStreamsInfo ; 
 scalar_t__ k7zIdUnpackInfo ; 

__attribute__((used)) static SRes SzReadStreamsInfo(CSzAr *p,
    CSzData *sd,
    UInt32 numFoldersMax, const CBuf *tempBufs, UInt32 numTempBufs,
    UInt64 *dataOffset,
    CSubStreamInfo *ssi,
    ISzAllocPtr alloc)
{
  UInt64 type;

  SzData_Clear(&ssi->sdSizes);
  SzData_Clear(&ssi->sdCRCs);
  SzData_Clear(&ssi->sdNumSubStreams);

  *dataOffset = 0;
  RINOK(ReadID(sd, &type));
  if (type == k7zIdPackInfo)
  {
    RINOK(ReadNumber(sd, dataOffset));
    RINOK(ReadPackInfo(p, sd, alloc));
    RINOK(ReadID(sd, &type));
  }
  if (type == k7zIdUnpackInfo)
  {
    RINOK(ReadUnpackInfo(p, sd, numFoldersMax, tempBufs, numTempBufs, alloc));
    RINOK(ReadID(sd, &type));
  }
  if (type == k7zIdSubStreamsInfo)
  {
    RINOK(ReadSubStreamsInfo(p, sd, ssi));
    RINOK(ReadID(sd, &type));
  }
  else
  {
    ssi->NumTotalSubStreams = p->NumFolders;
    // ssi->NumSubDigests = 0;
  }

  return (type == k7zIdEnd ? SZ_OK : SZ_ERROR_UNSUPPORTED);
}