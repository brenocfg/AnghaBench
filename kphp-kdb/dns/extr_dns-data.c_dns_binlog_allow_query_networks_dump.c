#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int ipv4; int prefix_bits; } ;
struct TYPE_3__ {int prefix_bits; int /*<<< orphan*/  ipv6; } ;

/* Variables and functions */
 TYPE_2__* BAQN ; 
 TYPE_1__* BAQN6 ; 
 int binlog_allow_query_networks ; 
 int binlog_allow_query_networks6 ; 
 char* show_ipv6 (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,...) ; 

int dns_binlog_allow_query_networks_dump (char *output, int avail_out) {
  int i, k = 0;
  for (i = 0; i < binlog_allow_query_networks; i++) {
    unsigned int ip = BAQN[i].ipv4;
    if (k) {
      if (avail_out <= 2) {
        return -1;
      }
      *output++ = ',';
      *output++ = ' ';
      avail_out -= 2;
    }
    int l = snprintf (output, avail_out, "%d.%d.%d.%d/%d", ip >> 24, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff, BAQN[i].prefix_bits);
    if (l >= avail_out) {
      return -1;
    }
    output += l;
    avail_out -= l;
    k++;
  }
  for (i = 0; i < binlog_allow_query_networks6; i++) {
    if (k) {
      if (avail_out <= 2) {
        return -1;
      }
      *output++ = ',';
      *output++ = ' ';
      avail_out -= 2;
    }
    int l = snprintf (output, avail_out, "%s/%d", show_ipv6 (BAQN6[i].ipv6), BAQN6[i].prefix_bits);
    if (l >= avail_out) {
      return -1;
    }
    output += l;
    avail_out -= l;
    k++;
  }
  if (avail_out <= 0) {
    return -1;
  }
  *output = 0;
  return 0;
}