#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int domains; TYPE_1__* domain; } ;
typedef  TYPE_2__ dns_write_iterator_t ;
struct TYPE_4__ {int len; int off; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dns_write_iterator_name_lookup (dns_write_iterator_t *B, char *name, int l) {
  int i;
  for (i = 0; i < B->domains; i++) {
    if (l == B->domain[i].len && !memcmp (name, B->domain[i].s, l)) {
      return B->domain[i].off;
    }
  }
  return -1;
}