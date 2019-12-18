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
struct mppe_state {int keybits; int* sesskey; } ;

/* Variables and functions */

__attribute__((used)) static void
MPPEReduceSessionKey(struct mppe_state *mp)
{
  switch(mp->keybits) {
  case 40:
    mp->sesskey[2] = 0x9e;
    mp->sesskey[1] = 0x26;
  case 56:
    mp->sesskey[0] = 0xd1;
  case 128:
    break;
  }
}