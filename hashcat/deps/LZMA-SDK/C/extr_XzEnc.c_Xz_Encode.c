#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ISeqOutStream ;
typedef  int /*<<< orphan*/  ISeqInStream ;
typedef  int /*<<< orphan*/  ICompressProgress ;
typedef  int /*<<< orphan*/  CXzProps ;
typedef  int /*<<< orphan*/  CXzEncHandle ;

/* Variables and functions */
 scalar_t__ SZ_ERROR_MEM ; 
 scalar_t__ SZ_OK ; 
 int /*<<< orphan*/  XzEnc_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XzEnc_Destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ XzEnc_Encode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XzEnc_SetProps (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_Alloc ; 
 int /*<<< orphan*/  g_BigAlloc ; 

SRes Xz_Encode(ISeqOutStream *outStream, ISeqInStream *inStream,
    const CXzProps *props, ICompressProgress *progress)
{
  SRes res;
  CXzEncHandle xz = XzEnc_Create(&g_Alloc, &g_BigAlloc);
  if (!xz)
    return SZ_ERROR_MEM;
  res = XzEnc_SetProps(xz, props);
  if (res == SZ_OK)
    res = XzEnc_Encode(xz, outStream, inStream, progress);
  XzEnc_Destroy(xz);
  return res;
}