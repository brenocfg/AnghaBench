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
struct TYPE_3__ {unsigned char* code; int* used; int* sums; int /*<<< orphan*/  d; int /*<<< orphan*/  mul1; int /*<<< orphan*/  mul0; } ;
typedef  TYPE_1__ perfect_hash ;

/* Variables and functions */
 int /*<<< orphan*/  READ_INT (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_code_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_sums_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_used_len (int /*<<< orphan*/ ) ; 

int ph_decode (perfect_hash *h, unsigned char *s) {
  unsigned char *st = s;

  READ_INT(s, h->d);
  READ_INT(s, h->mul0);
  READ_INT(s, h->mul1);

  h->code = s;
  s += get_code_len (h->d);
  h->used = (int *)s;
  s += get_used_len (h->d);
  h->sums = (int *)s;
  s += get_sums_len (h->d);

  return s - st;
}