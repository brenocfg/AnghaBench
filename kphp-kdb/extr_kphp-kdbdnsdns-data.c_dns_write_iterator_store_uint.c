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
struct TYPE_3__ {int avail_out; int wptr; } ;
typedef  TYPE_1__ dns_write_iterator_t ;

/* Variables and functions */
 unsigned int __builtin_bswap32 (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int,unsigned int*,int) ; 

__attribute__((used)) static int dns_write_iterator_store_uint (dns_write_iterator_t *B, unsigned int x) {
  if (B->avail_out < 4) {
    return -1;
  }
  B->avail_out -= 4;
  x = __builtin_bswap32 (x);
  memcpy (B->wptr, &x, 4);
  B->wptr += 4;
  return 0;
}