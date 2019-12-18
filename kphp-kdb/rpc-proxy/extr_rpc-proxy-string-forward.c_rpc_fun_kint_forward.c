#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long long step; unsigned long long tot_buckets; int /*<<< orphan*/ * buckets; scalar_t__* extensions_extra; } ;

/* Variables and functions */
 TYPE_1__* CC ; 
 int /*<<< orphan*/  TL_ERROR_PROXY_NO_TARGET ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t extension_firstint_num ; 
 unsigned long long extract_num (char*,int,char**) ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,int) ; 

int rpc_fun_kint_forward (void **IP, void **Data) {
  const char *key = *Data;
  int key_len = (long)*(Data + 1);
  int k = (long)CC->extensions_extra[extension_firstint_num];
  char *p1 = (char *) key, *p2;
  int clen = key_len;
  unsigned long long longhash = 0;
  int i;
  for (i = 0; i < k; i++) {
    longhash = extract_num (p1, clen, &p2);
    if ((long long) longhash == -1) {
      tl_fetch_set_error_format (TL_ERROR_PROXY_NO_TARGET, "Can not extract %d ints", k);
      return -1;
    }
    assert (p2 >= p1 && p2 <= p1 + clen);
    clen -= p2 - p1;
    p1 = p2;
  }
  if (CC->step > 0) {
    longhash /= CC->step;
  }
  *(Data + 2) = &CC->buckets[longhash % CC->tot_buckets];
  return 0;
}