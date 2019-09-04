#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  uid; struct school* sch; } ;
typedef  TYPE_1__ user_t ;
struct school {int /*<<< orphan*/  sch_type; int /*<<< orphan*/  sch_class; int /*<<< orphan*/  country; int /*<<< orphan*/  grad; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; int /*<<< orphan*/  spec_hashes; scalar_t__ spec; int /*<<< orphan*/  school; int /*<<< orphan*/  city; struct school* next; } ;
struct lev_school {char* spec; int type; int /*<<< orphan*/  sch_type; int /*<<< orphan*/  sch_class; int /*<<< orphan*/  country; int /*<<< orphan*/  grad; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; int /*<<< orphan*/  school; int /*<<< orphan*/  city; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_user_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ exact_strdup (char*,int) ; 
 TYPE_1__* get_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct school*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  q_sch_city ; 
 int /*<<< orphan*/  q_sch_class ; 
 int /*<<< orphan*/  q_sch_country ; 
 int /*<<< orphan*/  q_sch_grad ; 
 int /*<<< orphan*/  q_sch_id ; 
 int /*<<< orphan*/  q_sch_spec ; 
 int /*<<< orphan*/  save_words_hashlist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_add_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct school* zmalloc (int) ; 

__attribute__((used)) static int store_school (const struct lev_school *E, int sz) {
  const char *ptr = E->spec;
  int i, len = E->type & 0xff;
  user_t *U;
  struct school *S;

  if (sz < 26+len) { return -2; }

  assert (!ptr[len]);
  for (i = 0; i < len; i++) {
    assert ((unsigned char) ptr[i] >= ' ');
  }

  U = get_user (E->user_id);
  if (U) {
    S = zmalloc (sizeof (struct school));
    memset (S, 0, sizeof(*S));
    S->next = U->sch;
    U->sch = S;
#define CPY(__x,__f) user_add_field (U->uid, __f, S->__x = E->__x);  
    CPY(city, q_sch_city);
    CPY(school, q_sch_id);
    S->spec = 0;
    if (len) {
      S->spec = exact_strdup (E->spec, len);
      S->spec_hashes = save_words_hashlist (S->spec, 0, q_sch_spec);
      add_user_hashlist (U->uid, S->spec_hashes);
    }
    S->start = E->start;
    S->finish = E->finish;
    CPY(grad, q_sch_grad);
    CPY(country, q_sch_country);
    CPY(sch_class, q_sch_class);
    S->sch_type = E->sch_type;
#undef CPY
  }
  return 26+len;

}