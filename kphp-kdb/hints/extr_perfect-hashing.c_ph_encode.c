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
struct TYPE_3__ {int /*<<< orphan*/  d; int /*<<< orphan*/  sums; int /*<<< orphan*/  used; int /*<<< orphan*/  code; int /*<<< orphan*/  mul1; int /*<<< orphan*/  mul0; } ;
typedef  TYPE_1__ perfect_hash ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_INT (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_code_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_sums_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_used_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ph_encode (perfect_hash *h, unsigned char *s) {
  unsigned char *st = s;

  WRITE_INT(s, h->d);
  WRITE_INT(s, h->mul0);
  WRITE_INT(s, h->mul1);

  memcpy (s, h->code, get_code_len (h->d));
  s += get_code_len (h->d);
  memcpy (s, h->used, get_used_len (h->d));
  s += get_used_len (h->d);
  memcpy (s, h->sums, get_sums_len (h->d));
  s += get_sums_len (h->d);

  return s - st;
}