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
struct TYPE_2__ {char* origin; int origin_len; } ;

/* Variables and functions */
 TYPE_1__* Z ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  assert (char*) ; 
 size_t cur_zone_id ; 
 int get_name_f (char*,int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int append_origin_to_name (char *name, int name_len) {
  char *origin = Z[cur_zone_id].origin;
  assert (origin);
  int l = Z[cur_zone_id].origin_len;
  char *s = alloca (name_len + l + 1);
  memcpy (s, name, name_len);
  s[name_len] = '.';
  memcpy (s + name_len + 1, origin, l);
  l += name_len + 1;
  if (name[0] == '@' && name_len == 1) {
    s += 2;
    l -= 2;
  }
  return get_name_f (s, l, 1);
}