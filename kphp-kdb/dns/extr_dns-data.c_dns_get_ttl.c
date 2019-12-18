#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int ttl; } ;
typedef  TYPE_1__ dns_zone_t ;
struct TYPE_6__ {scalar_t__ data_len; scalar_t__ data; int /*<<< orphan*/  flag_has_ttl; } ;
typedef  TYPE_2__ dns_trie_record_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned int*,scalar_t__,int) ; 

__attribute__((used)) static unsigned int dns_get_ttl (dns_trie_record_t *R, dns_zone_t *Z) {
  if (!R->flag_has_ttl) {
    return Z->ttl;
  }
  unsigned int x;
  memcpy (&x, R->data + R->data_len, 4);
  return x;
}