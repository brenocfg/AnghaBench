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
struct item {int key_len; int value_len; int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int* B ; 
 int Bsize ; 
 scalar_t__* RR ; 
 size_t Rmax ; 
 scalar_t__ Rpos ; 
 size_t Rt ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

int tree_ifwrite (struct item *I) {
  if (Rt < Rmax && RR[Rt] == Rpos) {
    Rt ++;
    Rpos ++;
    if (2 + I->key_len + I->value_len < Bsize) {
      B[0] = I->key_len;
      memcpy (B + 1, I->key, 4 * I->key_len);
      B += (1 + I->key_len);
      B[0] = I->value_len;
      memcpy (B + 1, I->value, 4 * I->value_len);
      B += (1 + I->value_len);
      Bsize -= (2 + I->key_len + I->value_len);
      return 0;
    } else {
      Rmax = Rt;
      return -1;
    }
  } else {
    Rpos ++;
    return 0;
  }
}