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
struct TYPE_2__ {int data_type; int data_len; scalar_t__ flag_has_ttl; int* data; } ;
typedef  TYPE_1__ dns_trie_record_t ;

/* Variables and functions */
 size_t* RH ; 
#define  dns_type_a 131 
#define  dns_type_aaaa 130 
#define  dns_type_cname 129 
#define  dns_type_ptr 128 
 scalar_t__ max_hashed_records ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int /*<<< orphan*/ * records_buff ; 
 int records_hash_prime ; 
 scalar_t__ tot_hashed_records ; 

__attribute__((used)) static int dns_record_hash_lookup (int record_off) {
  if (RH == NULL) {
    return -1;
  }
  dns_trie_record_t *R = (dns_trie_record_t *) (&records_buff[record_off]);
  switch (R->data_type) {
    case dns_type_a:
    case dns_type_aaaa:
    case dns_type_ptr:
    case dns_type_cname:
      break;
    default:
      return -1;
  }
  unsigned int h1 = R->data_type, h2 = R->data_type;
  int sz = R->data_len;
  if (R->flag_has_ttl) {
    sz += 4;
  }
  int i;
  for (i = 0; i < sz; i++) {
    h1 = (257 * h1 + R->data[i]) % records_hash_prime;
    h2 = (3 * h2 + R->data[i]) % (records_hash_prime - 1);
  }
  h2++;
  while (RH[h1] >= 0) {
    dns_trie_record_t *Q = (dns_trie_record_t *) (&records_buff[RH[h1]]);
    if (Q->data_type == R->data_type && Q->data_len == R->data_len && Q->flag_has_ttl == R->flag_has_ttl && !memcmp (Q->data, R->data, sz)) {
      return RH[h1];
    }
    h1 += h2;
    if (h1 >= records_hash_prime) {
      h1 -= records_hash_prime;
    }
  }
  if (tot_hashed_records >= max_hashed_records) {
    return -1;
  }
  tot_hashed_records++;
  RH[h1] = record_off;
  return -1;
}