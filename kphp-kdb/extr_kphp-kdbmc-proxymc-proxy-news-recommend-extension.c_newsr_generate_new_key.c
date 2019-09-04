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
struct newsr_gather_extra {int mask; int st_time; int end_time; int id; int t; int timestamp; int request_tag; } ;

/* Variables and functions */
 int sprintf (char*,char*,int,int,int,int,int,int,int) ; 

int newsr_generate_new_key (char *buff, char *key, int len, void *E) {
  struct newsr_gather_extra *extra = E;
  int r = 0;
  r = sprintf (buff, "%%raw_recommend_updates%d_%d,%d_%d_%d_%d:%d", extra->mask, extra->st_time, extra->end_time, extra->id, extra->t, extra->timestamp, extra->request_tag);
  return r;
}