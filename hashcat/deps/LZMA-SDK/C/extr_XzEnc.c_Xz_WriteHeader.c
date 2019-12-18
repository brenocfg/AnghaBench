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
typedef  int /*<<< orphan*/  UInt32 ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISeqOutStream ;
typedef  int CXzStreamFlags ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 int /*<<< orphan*/  CrcCalc (scalar_t__*,int) ; 
 int /*<<< orphan*/  SetUi32 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBytes (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  XZ_SIG ; 
 size_t XZ_SIG_SIZE ; 
 int XZ_STREAM_FLAGS_SIZE ; 
 int XZ_STREAM_HEADER_SIZE ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static SRes Xz_WriteHeader(CXzStreamFlags f, ISeqOutStream *s)
{
  UInt32 crc;
  Byte header[XZ_STREAM_HEADER_SIZE];
  memcpy(header, XZ_SIG, XZ_SIG_SIZE);
  header[XZ_SIG_SIZE] = (Byte)(f >> 8);
  header[XZ_SIG_SIZE + 1] = (Byte)(f & 0xFF);
  crc = CrcCalc(header + XZ_SIG_SIZE, XZ_STREAM_FLAGS_SIZE);
  SetUi32(header + XZ_SIG_SIZE + XZ_STREAM_FLAGS_SIZE, crc);
  return WriteBytes(s, header, XZ_STREAM_HEADER_SIZE);
}