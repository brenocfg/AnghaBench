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
typedef  unsigned char unw_word ;

/* Variables and functions */
 int /*<<< orphan*/  B1 ; 
 int /*<<< orphan*/  UNW_DEC_COPY_STATE (int /*<<< orphan*/ ,unsigned char,void*) ; 
 int /*<<< orphan*/  UNW_DEC_LABEL_STATE (int /*<<< orphan*/ ,unsigned char,void*) ; 

__attribute__((used)) static unsigned char *
unw_decode_b1 (unsigned char *dp, unsigned char code, void *arg)
{
  unw_word label = (code & 0x1f);

  if ((code & 0x20) != 0)
    UNW_DEC_COPY_STATE(B1, label, arg);
  else
    UNW_DEC_LABEL_STATE(B1, label, arg);
  return dp;
}