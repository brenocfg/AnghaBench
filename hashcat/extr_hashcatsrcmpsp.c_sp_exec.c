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
typedef  size_t u64 ;
typedef  size_t u32 ;
struct TYPE_4__ {size_t cs_len; size_t* cs_buf; } ;
typedef  TYPE_1__ cs_t ;

/* Variables and functions */
 size_t CHARSIZ ; 

void sp_exec (u64 ctx, char *pw_buf, cs_t *root_css_buf, cs_t *markov_css_buf, u32 start, u32 stop)
{
  u64 v = ctx;

  cs_t *cs = &root_css_buf[start];

  u32 i;

  for (i = start; i < stop; i++)
  {
    const u64 m = v % cs->cs_len;
    const u64 d = v / cs->cs_len;

    v = d;

    const u32 k = cs->cs_buf[m];

    pw_buf[i - start] = (char) k;

    cs = &markov_css_buf[(i * CHARSIZ) + k];
  }
}