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
 int mode ; 
 size_t parse_pos ; 
 int sscanf (char*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,int*) ; 

unsigned parse_ip (void) {
  if (buff[parse_pos] == ',') {
    parse_pos ++;
  }
  unsigned a,b,c,d;
  int x;
  if (!mode) {
    assert (sscanf (buff + parse_pos, "\"%u.%u.%u.%u\"%n", &a, &b, &c, &d, &x) == 4);
  } else if (mode == 2) {
    assert (sscanf (buff + parse_pos, "%u.%u.%u.%u%n", &a, &b, &c, &d, &x) == 4);
  } else {
    assert (0);
  }
  assert (0 <= a && a < 256);
  assert (0 <= b && b < 256);
  assert (0 <= c && c < 256);
  assert (0 <= d && d < 256);
  parse_pos += x;
  assert (!buff[parse_pos] || buff[parse_pos] == ',');
  return (a << 24) + (b << 16) + (c << 8) + d;
}