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
 int /*<<< orphan*/  assert (int) ; 
 char* buff ; 
 int parse_pos ; 
 int sscanf (char*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,int*) ; 

void parse_ip_mask (unsigned *s, unsigned *f) {
  int x;
  unsigned a, b, c, d, m;
  assert (sscanf (buff + parse_pos, "%u.%u.%u.%u/%u%n", &a, &b, &c, &d, &m, &x) == 5);
  assert (0 <= a && a < 256);
  assert (0 <= b && b < 256);
  assert (0 <= c && c < 256);
  assert (0 <= d && d < 256);
  assert (0 < m && m <= 32);
  m = 32 - m;
  parse_pos += x;
  assert (!buff[parse_pos] || buff[parse_pos] == ',');
  *s = (a << 24) + (b << 16) + (c << 8) + d;
  m = (1 << m) - 1;
  //fprintf (stderr, "%x %x\n", *s, m);
  assert (!(*s & m));
  *f = *s + m;
}