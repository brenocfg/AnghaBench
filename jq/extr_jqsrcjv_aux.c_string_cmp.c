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
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/  const) ; 
 int jv_string_length_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_value (int /*<<< orphan*/  const) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int string_cmp(const void* pa, const void* pb){
  const jv* a = pa;
  const jv* b = pb;
  int lena = jv_string_length_bytes(jv_copy(*a));
  int lenb = jv_string_length_bytes(jv_copy(*b));
  int minlen = lena < lenb ? lena : lenb;
  int r = memcmp(jv_string_value(*a), jv_string_value(*b), minlen);
  if (r == 0) r = lena - lenb;
  return r;
}