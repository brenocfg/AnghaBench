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
typedef  int /*<<< orphan*/  CXzStreamFlags ;
typedef  int /*<<< orphan*/  CXzEncIndex ;

/* Variables and functions */
 scalar_t__ SZ_OK ; 
 int /*<<< orphan*/  XzEncIndex_Construct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XzEncIndex_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XzEncIndex_WriteFooter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ Xz_WriteHeader (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

SRes Xz_EncodeEmpty(ISeqOutStream *outStream)
{
  SRes res;
  CXzEncIndex xzIndex;
  XzEncIndex_Construct(&xzIndex);
  res = Xz_WriteHeader((CXzStreamFlags)0, outStream);
  if (res == SZ_OK)
    res = XzEncIndex_WriteFooter(&xzIndex, (CXzStreamFlags)0, outStream);
  XzEncIndex_Free(&xzIndex, NULL); // g_Alloc
  return res;
}