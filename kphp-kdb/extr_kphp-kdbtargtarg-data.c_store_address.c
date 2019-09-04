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
struct TYPE_3__ {int uid; scalar_t__ user_id; struct address* addr; } ;
typedef  TYPE_1__ user_t ;
struct lev_address_extended {int country; int city; int atype; int district; int station; int street; int* text; } ;
struct address {int atype; int country; int city; int district; int station; int street; void* name_hashes; void* name; void* house_hashes; void* house; struct address* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_user_hashlist (int,void*) ; 
 scalar_t__ debug_user_id ; 
 void* exact_strdup (int*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,int,int,int) ; 
 int now ; 
 int /*<<< orphan*/  q_adr_city ; 
 int /*<<< orphan*/  q_adr_country ; 
 int /*<<< orphan*/  q_adr_district ; 
 int /*<<< orphan*/  q_adr_house ; 
 int /*<<< orphan*/  q_adr_name ; 
 int /*<<< orphan*/  q_adr_station ; 
 int /*<<< orphan*/  q_adr_street ; 
 int /*<<< orphan*/  q_adr_type ; 
 void* save_words_hashlist (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  user_add_field (int,int /*<<< orphan*/ ,int) ; 
 int verbosity ; 
 struct address* zmalloc (int) ; 

__attribute__((used)) static void store_address (user_t *U, const struct lev_address_extended *E, int len) {
  int i, uid = U->uid;
  struct address *A = zmalloc (sizeof (struct address)), **to = &U->addr;

  if (verbosity > 1 && U->user_id == debug_user_id) {
    fprintf (stderr, "store_addr(user_id=%d, country=%d, city=%d), now=%d\n", debug_user_id, E->country, E->city, now);
  }

  A->next = *to;
#define CPY(__x,__f) user_add_field (uid, __f, A->__x = E->__x);  
  CPY(atype, q_adr_type);
  CPY(country, q_adr_country);
  CPY(city, q_adr_city);
  CPY(district, q_adr_district);
  CPY(station, q_adr_station);
  CPY(street, q_adr_street);
  A->house = A->name = 0;
  A->house_hashes = A->name_hashes = 0;
  if (len > 0 && !E->text[len]) {
    for (i = 0; i < len; i++) {
      if (E->text[i] == 9) {
        break;
      }
    }
    if (i > 0) {
      A->house = exact_strdup (E->text, i);
      A->house_hashes = save_words_hashlist (A->house, 0, q_adr_house);
      add_user_hashlist (U->uid, A->house_hashes);
    }
    if (i < len - 1) {
      A->name = exact_strdup (E->text + i + 1, len - i - 1);
      A->name_hashes = save_words_hashlist (A->name, 0, q_adr_name);
      add_user_hashlist (U->uid, A->name_hashes);
    }
  }
#undef CPY
  *to = A;
}