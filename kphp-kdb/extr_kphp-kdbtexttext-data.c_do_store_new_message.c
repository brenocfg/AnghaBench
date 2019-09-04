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
struct lev_add_message {int type; long long legacy_id; int date; int ua_hash; char* text; int* extra; scalar_t__ text_len; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FITS_AN_INT (long long) ; 
 int LEV_TX_ADD_MESSAGE_EXT ; 
 int LEV_TX_ADD_MESSAGE_EXT_LL ; 
 int LEV_TX_ADD_MESSAGE_LF ; 
 int LEV_TX_ADD_MESSAGE_MF ; 
 int MAX_EXTRA_MASK ; 
 unsigned int MAX_TEXT_LEN ; 
 struct lev_add_message* alloc_log_event (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conv_uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_adjust_text (char*,char*,scalar_t__) ; 
 int extra_mask_intcount (int) ; 
 int /*<<< orphan*/  memcpy (long long*,long long*,int) ; 
 int store_new_message (struct lev_add_message*,int) ; 
 int write_extra_mask ; 

int do_store_new_message (struct lev_add_message *M, int random_tag, char *text, long long legacy_id) {
  struct lev_add_message *E;
  char *ptr;
  int i;
  //user_t *U;

  if (conv_uid (M->user_id) < 0 || (unsigned) M->text_len >= MAX_TEXT_LEN) {
    return -1;
  }

  //U = get_user (M->user_id);

  int fmask = M->type >> 16, wmask = fmask & write_extra_mask;

  M->legacy_id = legacy_id;
  if (!FITS_AN_INT (legacy_id)) {
    M->date = M->type & 0xffff;
    M->type = LEV_TX_ADD_MESSAGE_EXT_LL | wmask;
    M->ua_hash = (M->ua_hash & 0xffffffffLL) | (legacy_id & 0xffffffff00000000LL);
  } else if (wmask & MAX_EXTRA_MASK) {
    M->date = M->type & 0xffff;
    M->type = LEV_TX_ADD_MESSAGE_EXT | wmask;
  } else if (M->type & -0x1000) {
    M->date = M->type & 0xffff;
    M->type = LEV_TX_ADD_MESSAGE_LF;
  } else {
    M->type |= LEV_TX_ADD_MESSAGE_MF;
  }

  int extra_len = 4 * extra_mask_intcount (fmask);
  int w_extra_len = 4 * extra_mask_intcount (wmask);

  E = alloc_log_event (M->type, sizeof (struct lev_add_message) + w_extra_len + M->text_len + 1, M->user_id);
  memcpy (&E->legacy_id, &M->legacy_id, (char *) &M->text - (char *) &M->legacy_id);

  ptr = E->text + w_extra_len;
  if (!text) {
    text = M->text + extra_len;
  }

  int *E_extra = E->extra, *M_extra = M->extra;

  for (i = 1; i < MAX_EXTRA_MASK; i <<= 1) {
    if (wmask & i) {
      if (i < 256) {
        *E_extra++ = *M_extra++;
      } else {
        *(long long *) E_extra = *(long long *) M_extra;
        E_extra += 2;
        M_extra += 2;
      }
    } else if (fmask & i) {
      M_extra += (i < 256 ? 1 : 2);
    }
  }

  assert ((char *) E_extra == ptr);

  copy_adjust_text (ptr, text, M->text_len);

  return store_new_message (E, random_tag);
}