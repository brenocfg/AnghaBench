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
 scalar_t__ BUFF_LEN ; 
 scalar_t__ buff ; 
 int /*<<< orphan*/  flush_buff () ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 int min (int,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ wptr ; 

void write_buff (const char *s, int l) {
  while (l > 0) {
    if (unlikely (wptr == buff + BUFF_LEN)) {
      flush_buff ();
    }
    int ll = min (l, buff + BUFF_LEN -  wptr);
    memcpy (wptr, s, ll);
    wptr += ll;
    s += ll;
    l -= ll;
  }

}