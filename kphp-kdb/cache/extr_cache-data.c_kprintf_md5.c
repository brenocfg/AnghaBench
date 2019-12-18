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
struct TYPE_3__ {int* c; } ;
typedef  TYPE_1__ md5_t ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,char*,char*) ; 

__attribute__((used)) static void kprintf_md5 (char *msg, md5_t *m, int len) {
  static char output[33], hcyf[16] = "0123456789abcdef";
  int i;
  for (i = 0; i < len; i++) {
    output[2*i] = hcyf[(m->c[i] >> 4)];
    output[2*i+1] = hcyf[m->c[i] & 15];
  }
  output[2*len] = 0;
  kprintf ("%s%s\n", msg, output);
}