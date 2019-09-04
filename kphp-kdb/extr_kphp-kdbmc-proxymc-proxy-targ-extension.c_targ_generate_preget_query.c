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
struct TYPE_2__ {int tot_buckets; } ;

/* Variables and functions */
 TYPE_1__* CC ; 
 int* Q ; 
 int QLsave ; 
 int* Qsave ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 
 int sprintf (char*,char*,scalar_t__,int) ; 
 scalar_t__ tag_save ; 

__attribute__((used)) static int targ_generate_preget_query (char *buff, const char *key, int key_len, void *E, int n) {
  if (!tag_save) {
    return 0;
  }
  if (tag_save > 0) {
    int r = sprintf (buff, "set temp%d 0 0 %d\r\n", tag_save, QLsave);
    memcpy (buff + r, Qsave, QLsave);
    return r + QLsave;
  } else if (tag_save < 0) {
    int i;
    int len = 0;
    Q[0] = 0x30303030;
    for (i = 0; i < QLsave; i++) if (Qsave[i] % CC->tot_buckets == n) {
      Q[++len] = Qsave[i];
    }
    int r = sprintf (buff, "set xtemp%d 0 0 %d\r\n", tag_save, 4 * len + 4);
    memcpy (buff + r, Q, 4 * len + 4);
    return r + 4 * len + 4;
  } else {
    return 0;
  }
}