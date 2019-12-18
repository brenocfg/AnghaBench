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
typedef  int /*<<< orphan*/  sz ;
struct connection {int /*<<< orphan*/  Tmp; } ;

/* Variables and functions */
 int read_in (int /*<<< orphan*/ ,int*,int) ; 
 int* value_buff ; 

int parse_path (struct connection *c) {
  int sz;
  if (read_in (c->Tmp, &sz, sizeof (sz)) != sizeof (sz)) {
    return -1;
  }
  if (read_in (c->Tmp, value_buff, sz) != sz) {
    return -2;
  }
  value_buff[sz] = 0;
  return 0;
}