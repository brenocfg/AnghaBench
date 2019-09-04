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
struct TYPE_3__ {int /*<<< orphan*/  uid; struct company* work; } ;
typedef  TYPE_1__ user_t ;
struct lev_company {char* text; int type; int /*<<< orphan*/  country; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; int /*<<< orphan*/  company; int /*<<< orphan*/  city; int /*<<< orphan*/  user_id; } ;
struct company {void* job_hashes; void* job; void* name_hashes; void* company_name; int /*<<< orphan*/  country; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; int /*<<< orphan*/  company; int /*<<< orphan*/  city; struct company* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_user_hashlist (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* exact_strdup (char*,int) ; 
 TYPE_1__* get_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct company*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  q_company_name ; 
 int /*<<< orphan*/  q_job ; 
 void* save_words_hashlist (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct company* zmalloc (int) ; 

__attribute__((used)) static int store_company (const struct lev_company *E, int sz) {
  const char *ptr = E->text;
  int i, j = 0, len = E->type & 0x1ff;
  user_t *U;
  struct company *C;

  if (sz < 22+len) { return -2; }

  assert (!ptr[len]);
  for (i = 0; i < len; i++) {
    if (ptr[i] == 9) { j++; }
    else { 
      assert ((unsigned char) ptr[i] >= ' ');
    }
  }
  assert (j == 1);

  U = get_user (E->user_id);
  if (U) {
    C = zmalloc (sizeof (struct company));
    memset (C, 0, sizeof(*C));
    C->next = U->work;
    U->work = C;
#define CPY(__x) C->__x = E->__x;  
    CPY(city);
    CPY(company);
    CPY(start);
    CPY(finish);
    CPY(country);
#undef CPY
    for (i = 0; i < len; i++) { 
      if (ptr[i] == 9) { break; }
    }
    if (i > 0) {
      C->company_name = exact_strdup (E->text, i);
      C->name_hashes = save_words_hashlist (C->company_name, 0, q_company_name);
      add_user_hashlist (U->uid, C->name_hashes);
    }
    if (i < len - 1) {
      ptr += i+1;
      C->job = exact_strdup (E->text+i+1, len-i-1);
      C->job_hashes = save_words_hashlist (C->job, 0, q_job);
      add_user_hashlist (U->uid, C->job_hashes);
    }
  }
  return 22+len;
}