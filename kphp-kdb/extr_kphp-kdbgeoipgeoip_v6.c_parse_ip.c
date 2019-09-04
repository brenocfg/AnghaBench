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
struct ipv6 {int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char* buff ; 
 size_t parse_pos ; 

struct ipv6 parse_ip (void) {
  if (buff[parse_pos] == ',') {
    parse_pos ++;
  }
  while (buff[parse_pos] == ' ') {
    parse_pos ++;
  }
  assert (buff[parse_pos ++] == '"');
  int p = 0;
  struct ipv6 a;
  a.data[0] = 0;

  while (buff[parse_pos] != '"' ) {
    if (buff[parse_pos] == ':') {
      assert (p <= 6);
      a.data[++p] = 0;
    } else {
      char c = buff[parse_pos];
      assert (('0' <= c && c <= '9') || (c >= 'a' && c <= 'f'));
      if (c <= '9' && c >= '0') {
        a.data[p] = a.data[p] * 16 + c - '0';
      } else {
        a.data[p] = a.data[p] * 16 + c + 10 - 'a';
      }
    }
    parse_pos ++;
  }
  //assert (p == 7);
  assert (buff[parse_pos ++] == '"');
  assert (!buff[parse_pos] || buff[parse_pos] == ',' || buff[parse_pos] == 10 || buff[parse_pos] == 13);
  return a;
}