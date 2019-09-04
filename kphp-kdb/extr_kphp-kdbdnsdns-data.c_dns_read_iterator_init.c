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
struct TYPE_3__ {unsigned char* start; unsigned char* rptr; int ilen; int avail_in; } ;
typedef  TYPE_1__ dns_read_iterator_t ;

/* Variables and functions */

__attribute__((used)) static void dns_read_iterator_init (dns_read_iterator_t *B, unsigned char *in, int ilen) {
  B->start = B->rptr = in;
  B->ilen = B->avail_in = ilen;
}