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
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  GetUi32 (int /*<<< orphan*/  const*) ; 

void AesCbc_Init(UInt32 *p, const Byte *iv)
{
  unsigned i;
  for (i = 0; i < 4; i++)
    p[i] = GetUi32(iv + i * 4);
}