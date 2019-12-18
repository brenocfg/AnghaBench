#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  root; } ;
struct TYPE_12__ {TYPE_1__ s; } ;
typedef  TYPE_2__ subscribers ;
struct TYPE_13__ {int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ pli ;
typedef  int /*<<< orphan*/  ll ;
struct TYPE_14__ {int y; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SUBSCR ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnt_srt (TYPE_4__*,int,TYPE_3__*) ; 
 int dl_abs (int /*<<< orphan*/ ) ; 
 int engine_n ; 
 int /*<<< orphan*/  flush_news () ; 
 TYPE_2__* get_subscribers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redirect_news_ (int /*<<< orphan*/ ,int,int,int,char*,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  redirect_news_cnt ; 
 int redirect_news_len ; 
 int /*<<< orphan*/  redirect_news_twice_cnt ; 
 TYPE_4__* sb ; 
 TYPE_3__* sb2 ; 
 int treap_conv_to_array (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 

void redirect_news (ll id, int x, int y, int ttl, char *text, int text_n) {
  subscribers *s = get_subscribers (id, 0);
  //dbg ("redirect news %lld : %p\n", id, s);

  if (s == NULL) {
    return;
  }

  ttl--;

  int nn = treap_conv_to_array (s->s.root, sb, MAX_SUBSCR), n = 0, i, j, f = 0;
  for (i = 0; i < nn; i++) {
    if ((sb[i].y & x) == y) {
      sb[n++] = sb[i];
    }
  }

  pli *a = sb2;
  cnt_srt (sb, n, a);
  //dbg ("redirect news : to (%lld ... )\n", a[0].x);
/*  for (i = 0; i < n; i++) {
    fprintf (stderr, "[%lld,%d]%c", a[i].x, a[i].y, " \n"[i + 1 == n]);
  }*/

  if (ttl == 0) {
    STAT (redirect_news_twice_cnt);
  }
  STAT (redirect_news_cnt);
  redirect_news_len += n;

  for (i = j = 0; i <= n; i++) {
    if (i == n || dl_abs (a[i].x) % engine_n != dl_abs (a[j].x) % engine_n ||
        i - j > 50000) {
//      fprintf (stderr, "%d<--->%d\n", j, i);
      f = 1;
      redirect_news_ (id, x, y, ttl, text, text_n, a + j, i - j);
      j = i;
    }
  }

  if (f) {
    flush_news();
  }
}