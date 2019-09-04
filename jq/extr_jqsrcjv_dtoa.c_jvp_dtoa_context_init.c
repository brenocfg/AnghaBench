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
struct dtoa_context {scalar_t__ p5s; scalar_t__* freelist; } ;

/* Variables and functions */

void jvp_dtoa_context_init(struct dtoa_context* C) {
  int i;
  for (i=0; i<(int)(sizeof(C->freelist)/sizeof(C->freelist[0])); i++) {
    C->freelist[i] = 0;
  }
  C->p5s = 0;
}