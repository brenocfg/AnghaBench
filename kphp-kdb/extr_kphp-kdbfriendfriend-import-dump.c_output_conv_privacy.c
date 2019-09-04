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
struct lev_set_privacy {int* List; int /*<<< orphan*/  type; int /*<<< orphan*/  key; int /*<<< orphan*/  user_id; } ;
typedef  int /*<<< orphan*/  privacy_key_t ;

/* Variables and functions */
 int CAT_FR_ALL ; 
 int CAT_FR_FR ; 
 int CAT_FR_PACKED ; 
 int /*<<< orphan*/  LEV_FR_SET_PRIVACY_FORCE ; 
 int PL_M_ALLOW ; 
 int PL_M_CAT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  user_id ; 
 struct lev_set_privacy* write_alloc (int) ; 

void output_conv_privacy (privacy_key_t key, int priv, const char *rules) {
  int res = -1;
  const char *aux = "";
  assert (key);

//  fprintf (stderr, "output_conv_privacy(%016llx, %d, %s)\n", key, priv, rules);

  if (priv < 0) {
    res = ((-priv & 0x1fe) >> 1);
    if (!res) {
      res = CAT_FR_PACKED;
    }
    res |= PL_M_CAT | PL_M_ALLOW;
  } else if (priv*2 < strlen (rules)) {
    aux = rules + priv*2;
  } else {
    aux = "*A";
  }

  if (aux[0] == '*') {
    switch (aux[1]) {
    case '0':
      res = PL_M_ALLOW + PL_M_CAT + CAT_FR_PACKED;
      break;
    case 'A':
      res = PL_M_ALLOW + PL_M_CAT + CAT_FR_ALL;
      break;
    case 'G':
      res = PL_M_ALLOW + PL_M_CAT + CAT_FR_FR;
      break;
    }
  }

  struct lev_set_privacy *E = write_alloc (16 + (res != -1 ? 4 : 0));
  E->type = LEV_FR_SET_PRIVACY_FORCE;
  E->user_id = user_id;
  E->key = key;
  if (res != -1) {
    E->type++;
    E->List[0] = res;
  }

//  fprintf (stderr, " = %08x\n", res);
}