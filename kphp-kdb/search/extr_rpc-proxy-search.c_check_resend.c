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
struct search_extra {int sent_limit; double limit; } ;
struct gather {int tot_num; TYPE_1__* List; struct search_extra* extra; } ;
struct TYPE_2__ {int bytes; int* data; } ;

/* Variables and functions */
 int TL_SEARCH_RESULT ; 
 scalar_t__ resend_one (struct gather*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,...) ; 

int check_resend (struct gather *G) {
  int i;
  struct search_extra *extra = G->extra;
  int total_sum = 0;
  int total_count = 0;
  for (i = 0; i < G->tot_num; i++) if (G->List[i].bytes >= 16 && G->List[i].data[0] == TL_SEARCH_RESULT) {
    int a = G->List[i].data[2];
    int b = G->List[i].data[3];
    if (b == extra->sent_limit && a > b) {
      total_count ++;
    }
    total_sum += b;
  }
  vkprintf (3, "total_sum = %d, limit = %d, count = %d, tot_num = %d\n", total_sum, extra->limit, total_count, G->tot_num);
  if (total_sum < 1.5 * extra->limit && total_count < 0.1 * G->tot_num) {
    int cc = 0;
    for (i = 0; i < G->tot_num; i++) if (G->List[i].bytes >= 16 && G->List[i].data[0] == TL_SEARCH_RESULT) {
      int a = G->List[i].data[2];
      int b = G->List[i].data[3];
      if (b == extra->sent_limit && a > b) {
        vkprintf (4, "Resending #%d\n", i);
        cc += resend_one (G, i);
      }
    }
    vkprintf (4, "result = %d\n", cc);
    return cc;
  } else {
    return 0;
  }
}