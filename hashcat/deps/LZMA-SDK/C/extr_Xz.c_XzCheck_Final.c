#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt64 ;
struct TYPE_3__ {int mode; int /*<<< orphan*/  sha; int /*<<< orphan*/  crc64; int /*<<< orphan*/  crc; } ;
typedef  TYPE_1__ CXzCheck ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int CRC64_GET_DIGEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRC_GET_DIGEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetUi32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sha256_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  XZ_CHECK_CRC32 130 
#define  XZ_CHECK_CRC64 129 
#define  XZ_CHECK_SHA256 128 

int XzCheck_Final(CXzCheck *p, Byte *digest)
{
  switch (p->mode)
  {
    case XZ_CHECK_CRC32:
      SetUi32(digest, CRC_GET_DIGEST(p->crc));
      break;
    case XZ_CHECK_CRC64:
    {
      int i;
      UInt64 v = CRC64_GET_DIGEST(p->crc64);
      for (i = 0; i < 8; i++, v >>= 8)
        digest[i] = (Byte)(v & 0xFF);
      break;
    }
    case XZ_CHECK_SHA256:
      Sha256_Final(&p->sha, digest);
      break;
    default:
      return 0;
  }
  return 1;
}