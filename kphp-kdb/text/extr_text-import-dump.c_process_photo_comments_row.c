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
struct lev_add_message {int user_id; int peer_msg_id; int text_len; char* text; int /*<<< orphan*/  ua_hash; void* front; void* port; void* ip; void* date; void* peer_id; void* legacy_id; scalar_t__ type; } ;

/* Variables and functions */
 void** I ; 
 int* L ; 
 scalar_t__ LEV_TX_ADD_MESSAGE ; 
 scalar_t__ LEV_TX_ADD_MESSAGE_EXT_ZF ; 
 char** S ; 
 int /*<<< orphan*/  adj_rec ; 
 scalar_t__ conv_uid (int) ; 
 int list_id ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 size_t pc_date ; 
 size_t pc_from_id ; 
 size_t pc_front ; 
 size_t pc_id ; 
 size_t pc_ip ; 
 size_t pc_local_id ; 
 size_t pc_message ; 
 size_t pc_owner_id ; 
 size_t pc_photo_id ; 
 size_t pc_port ; 
 size_t pc_ua_hash ; 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strtoull (char*,int /*<<< orphan*/ ,int) ; 
 struct lev_add_message* write_alloc (int) ; 

void process_photo_comments_row (void) {
  int i, len, from_id = I[pc_from_id];
  int extra_id = I[pc_local_id], extra_bytes = (extra_id ? 4 : 0);
  char *ptr, *str;
  list_id = I[pc_owner_id];
  if (conv_uid (list_id) < 0 || !list_id || !from_id) {
    return;
  }
  if (L[pc_message] == 2 && !strcmp (S[pc_message], "\\N")) {
    L[pc_message] = 0;
    S[pc_message][0] = 0;
  }
  static char kludge[32];
  int kludge_bytes = from_id < 0 ? sprintf (kludge, "\x1ras %d\t", list_id) : 0;
  struct lev_add_message *E = write_alloc (sizeof (struct lev_add_message) + extra_bytes + kludge_bytes + L[pc_message] + 1);
  E->type = extra_bytes ? LEV_TX_ADD_MESSAGE_EXT_ZF + 1 : LEV_TX_ADD_MESSAGE;
  E->user_id = list_id;
  E->legacy_id = I[pc_id];
  E->peer_id = I[pc_photo_id];
  E->peer_msg_id = (from_id >= 0 ? from_id : -from_id);
  E->date = I[pc_date];
  E->ip = I[pc_ip];
  E->port = I[pc_port];
  E->front = I[pc_front];
  E->ua_hash = strtoull (S[pc_ua_hash], 0, 10);
  len = L[pc_message];
  E->text_len = kludge_bytes + len;
  ptr = E->text;
  if (extra_bytes) {
    *((int *) ptr) = extra_id;
    ptr += 4;
  }
  if (kludge_bytes) {
    memcpy (ptr, kludge, kludge_bytes);
    ptr += kludge_bytes;
  }
  str = S[pc_message];
  for (i = 0; i < len; i++) {
    if ((unsigned char) str[i] < ' ' && str[i] != '\t') {
      *ptr++ = ' ';
    } else {
      *ptr++ = str[i];
    }
  }
  *ptr++ = 0;

  adj_rec++;
}