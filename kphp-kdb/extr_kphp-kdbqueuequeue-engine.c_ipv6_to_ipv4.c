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

/* Variables and functions */
 char* ip_buff ; 
 int md5_last_bits (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,...) ; 
 int sscanf (char*,char*,int*,int*) ; 

int ipv6_to_ipv4 (void) {
  int i;
  for (i = 0; ip_buff[i]; i++) {
    if ('A' <= ip_buff[i] && ip_buff[i] < 'Z') {
      ip_buff[i] = ip_buff[i] - 'A' + 'a';
    }
  }
  int l = 0, r = i;
  if (ip_buff[0] == ':' && ip_buff[1] == ':') {
    l++;
  } else {
    if (r > 2 && ip_buff[r - 1] == ':' && ip_buff[r - 2] == ':') {
      r--;
    }
  }
  ip_buff[r] = ':';

  char *x[9];
  int cnt = 0;
  for (i = l; i <= r && cnt <= 8; i++) {
    x[cnt++] = ip_buff + i;
    while (ip_buff[i] != ':') {
      i++;
    }
    ip_buff[i] = 0;
  }

  if (cnt < 2 || cnt > 8) {
    return 0;
  }
  if (cnt < 8) {
    int k = -1;
    for (i = 0; i < cnt; i++) {
      if (x[i][0] == 0) {
        if (k >= 0) {
          return 0;
        }
        k = i;
      }
    }
    if (k < 0) {
      return 0;
    }
    for (i = cnt - 1; i > k; i--) {
      x[i - cnt + 8] = x[i];
    }
    for (i = k - cnt + 8; i >= k; i--) {
      x[i] = "0";
    }
  }
  int y[8];
  for (i = 0; i < 8; i++) {
    int pos = -1;
    if (sscanf (x[i], "%x%n", &y[i], &pos) < 1 || y[i] >= 65536 || y[i] < 0 || x[i][pos]) {
      return 0;
    }
  }

  char buf[17];
  sprintf (buf, "%04x%04x", y[0], y[1]);
  int f1 = md5_last_bits (buf);
  sprintf (buf, "%04x%04x", y[2], y[3]);
  int f2 = md5_last_bits (buf);
  sprintf (buf, "%04x%04x%04x%04x", y[4], y[5], y[6], y[7]);
  int f3 = md5_last_bits (buf);
  int n1 = ((f1 >> 4) & 0x1f) | 0xe0;
  int n2 = ((f1 & 0x0f) << 4) | (f2 >> 8);
  int n3 = f2 & 0xff;
  int n4 = f3 & 0xff;
  sprintf (ip_buff, "%d.%d.%d.%d", n1, n2, n3, n4);
  return 1;
}