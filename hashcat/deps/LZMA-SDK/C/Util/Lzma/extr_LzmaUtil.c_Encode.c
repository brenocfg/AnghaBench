#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt64 ;
struct TYPE_5__ {size_t (* Write ) (TYPE_1__*,scalar_t__*,size_t) ;} ;
typedef  scalar_t__ SRes ;
typedef  TYPE_1__ ISeqOutStream ;
typedef  int /*<<< orphan*/  ISeqInStream ;
typedef  int /*<<< orphan*/  CLzmaEncProps ;
typedef  scalar_t__ CLzmaEncHandle ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 int LZMA_PROPS_SIZE ; 
 int /*<<< orphan*/  LzmaEncProps_Init (int /*<<< orphan*/ *) ; 
 scalar_t__ LzmaEnc_Create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LzmaEnc_Destroy (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ LzmaEnc_Encode (scalar_t__,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ LzmaEnc_SetProps (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ LzmaEnc_WriteProperties (scalar_t__,scalar_t__*,size_t*) ; 
 scalar_t__ SZ_ERROR_MEM ; 
 scalar_t__ SZ_ERROR_WRITE ; 
 scalar_t__ SZ_OK ; 
 int /*<<< orphan*/  UNUSED_VAR (char*) ; 
 int /*<<< orphan*/  g_Alloc ; 
 size_t stub1 (TYPE_1__*,scalar_t__*,size_t) ; 

__attribute__((used)) static SRes Encode(ISeqOutStream *outStream, ISeqInStream *inStream, UInt64 fileSize, char *rs)
{
  CLzmaEncHandle enc;
  SRes res;
  CLzmaEncProps props;

  UNUSED_VAR(rs);

  enc = LzmaEnc_Create(&g_Alloc);
  if (enc == 0)
    return SZ_ERROR_MEM;

  LzmaEncProps_Init(&props);
  res = LzmaEnc_SetProps(enc, &props);

  if (res == SZ_OK)
  {
    Byte header[LZMA_PROPS_SIZE + 8];
    size_t headerSize = LZMA_PROPS_SIZE;
    int i;

    res = LzmaEnc_WriteProperties(enc, header, &headerSize);
    for (i = 0; i < 8; i++)
      header[headerSize++] = (Byte)(fileSize >> (8 * i));
    if (outStream->Write(outStream, header, headerSize) != headerSize)
      res = SZ_ERROR_WRITE;
    else
    {
      if (res == SZ_OK)
        res = LzmaEnc_Encode(enc, outStream, inStream, NULL, &g_Alloc, &g_Alloc);
    }
  }
  LzmaEnc_Destroy(enc, &g_Alloc, &g_Alloc);
  return res;
}