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
struct newsr_gather_extra {int request_tag; } ;

/* Variables and functions */
 int MAX_RES ; 
 int* Q ; 
 int* QN ; 
 int* R ; 
 int R_common_len ; 
 int* Rfirst ; 
 int* Rlen ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int const) ; 
 int sprintf (char*,char*,int,int const) ; 

int newsr_generate_preget_query (char *buff, const char *key, int key_len, void *E, int n) {
  if (!Rlen[n]) return 0;
  struct newsr_gather_extra* extra = E;
  int len = Rlen[n];
  int j, x = Rfirst[n], k = R_common_len;
  assert (R[0] == 0x31303030);
  for (j = 0; j < len; j++) {
    assert (x >= 0);
    assert (k + 2 <= MAX_RES + 1);
    R[k++] = Q[2 * x + 0];
    R[k++] = Q[2 * x + 1];
    x = QN[x];
  }
	
  assert (x == -1 && len > 0);
  const int data_len = k << 2;
  int r = sprintf (buff, "set urlist%d 0 0 %d\r\n", extra->request_tag, data_len);
  memcpy (buff + r, R, data_len);
  r += data_len;
  return r;
}