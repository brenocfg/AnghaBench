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
struct news_gather_extra {int request_tag; } ;

/* Variables and functions */
 int MAX_RES ; 
 scalar_t__ NEWS_COMM_EXTENSION ; 
 scalar_t__ NEWS_G_EXTENSION ; 
 scalar_t__ NEWS_UG_EXTENSION ; 
 int* Q ; 
 int* QN ; 
 int* R ; 
 int* Rfirst ; 
 int* Rlen ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 
 int sprintf (char*,char*,char*,int,int) ; 

int news_generate_preget_query (char *buff, const char *key, int key_len, void *E, int n) {
  if (!Rlen[n]) return 0;
  struct news_gather_extra* extra = E;
  int len = Rlen[n];
  int j, x = Rfirst[n];
  R[0] = ((NEWS_UG_EXTENSION || NEWS_G_EXTENSION) ? 0x30303030 : 0x32303030);
  assert (1 + len * ((NEWS_UG_EXTENSION || NEWS_G_EXTENSION) ? 1 : 3) <= MAX_RES);
  for (j = 0; j < len; j++) {
    assert (x >= 0);
    if ((NEWS_UG_EXTENSION || NEWS_G_EXTENSION)){
      R[j+1] = Q[x];
    } else {
      R[3*j+1] = Q[3*x];
      R[3*j+2] = Q[3*x+1];
      R[3*j+3] = Q[3*x+2];
    }
    x = QN[x];
  }
	
  assert (x == -1 && len > 0);
	if (NEWS_COMM_EXTENSION) {
	  len *= 3;
	}
  int r;
  assert (NEWS_COMM_EXTENSION || (NEWS_UG_EXTENSION || NEWS_G_EXTENSION));
  int ug_mode = (NEWS_UG_EXTENSION || NEWS_G_EXTENSION) ? 0 : 1;
  r = sprintf (buff, "set %slist%d 0 0 %d\r\n", ug_mode <= 0 ? "user" : "object", extra->request_tag, len*4+4);
  memcpy (buff + r, R, len * 4 + 4);
  r += len * 4 + 4;
  return r;
}