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
struct TYPE_3__ {unsigned char* start; unsigned char* wptr; int olen; int avail_out; int /*<<< orphan*/  domain_buff; int /*<<< orphan*/  domain_wptr; scalar_t__ domains; } ;
typedef  TYPE_1__ dns_write_iterator_t ;

/* Variables and functions */

__attribute__((used)) static void dns_write_iterator_init (dns_write_iterator_t *B, unsigned char *out, int olen) {
  B->start = B->wptr = out;
  B->olen = B->avail_out = olen;
  B->domains = 0;
  B->domain_wptr = B->domain_buff;
}