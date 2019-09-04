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
typedef  int /*<<< orphan*/  len ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int*,int) ; 

int blist_encode_list (int *P, int len, int tot_items, unsigned char *res) {
  int r;
  memcpy (res, &len, r = sizeof (len));
  memcpy (res + sizeof (len), P, r += sizeof (*P) * len);
  return r;
}