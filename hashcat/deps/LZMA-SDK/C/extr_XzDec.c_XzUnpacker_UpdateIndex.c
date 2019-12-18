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
typedef  int /*<<< orphan*/  UInt64 ;
struct TYPE_3__ {unsigned int indexSize; int /*<<< orphan*/  numBlocks; int /*<<< orphan*/  sha; } ;
typedef  TYPE_1__ CXzUnpacker ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  Sha256_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int Xz_WriteVarInt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void XzUnpacker_UpdateIndex(CXzUnpacker *p, UInt64 packSize, UInt64 unpackSize)
{
  Byte temp[32];
  unsigned num = Xz_WriteVarInt(temp, packSize);
  num += Xz_WriteVarInt(temp + num, unpackSize);
  Sha256_Update(&p->sha, temp, num);
  p->indexSize += num;
  p->numBlocks++;
}