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
struct TYPE_3__ {int code_len; int len; char* str; } ;
typedef  TYPE_1__ word_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  writeout (char*,int) ; 

int write_word_dictionary_word (word_t *W) {
  static char buff[8];
  int sz, i = 1;
  assert (W->code_len > 0 && W->code_len <= 32 && W->len < 256);
  buff[0] = W->code_len;
  buff[1] = W->len;
  writeout (buff, 2);
  writeout (W->str, W->len);
  sz = W->len + 2;
  i = -sz & 3;
  writeout (buff+2, i);
  return sz + i;
}