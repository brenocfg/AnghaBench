#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {void* odd; void* evn; } ;
typedef  TYPE_1__ cf_sha3_bi ;

/* Variables and functions */
 void* rotl32 (void*,int) ; 

__attribute__((used)) static inline void rotl_bi_n(cf_sha3_bi *out, const cf_sha3_bi *in, uint8_t rot)
{
  uint8_t half = rot >> 1;

  /* nb. rot is a constant, so this isn't a branch leak. */
  if (rot & 1)
  {
    out->odd = rotl32(in->evn, half + 1);
    out->evn = rotl32(in->odd, half);
  } else {
    out->evn = rotl32(in->evn, half);
    out->odd = rotl32(in->odd, half);
  }
}