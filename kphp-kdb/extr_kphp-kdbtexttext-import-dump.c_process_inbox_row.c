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
struct lev_add_message {int user_id; int legacy_id; int peer_id; int peer_msg_id; int date; int ip; int port; int front; int text_len; char* text; int /*<<< orphan*/  ua_hash; scalar_t__ type; } ;

/* Variables and functions */
 int* I ; 
 int* L ; 
 scalar_t__ LEV_TX_ADD_MESSAGE ; 
 char** S ; 
 int /*<<< orphan*/  TXF_FRIENDS ; 
 int /*<<< orphan*/  TXF_SPAM ; 
 scalar_t__ TXF_UNREAD ; 
 int /*<<< orphan*/  adj_rec ; 
 scalar_t__ conv_uid (int) ; 
 int force_read_threshold ; 
 size_t ib_date ; 
 size_t ib_from_id ; 
 size_t ib_front ; 
 size_t ib_id ; 
 size_t ib_ip ; 
 size_t ib_message ; 
 size_t ib_port ; 
 size_t ib_read_date ; 
 size_t ib_read_state ; 
 size_t ib_title ; 
 size_t ib_to_id ; 
 size_t ib_to_shown ; 
 size_t ib_ua_hash ; 
 scalar_t__ is_friend (int,int) ; 
 int list_id ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strtoull (char*,int /*<<< orphan*/ ,int) ; 
 struct lev_add_message* write_alloc (int) ; 

void process_inbox_row (void) {
  int user_id = I[ib_from_id];
  int i, len;
  char *ptr, *str;
  list_id = I[ib_to_id]; 
  if (conv_uid (list_id) < 0 || list_id <= 0 || user_id <= 0) {
    return;
  }
  if (I[ib_date] && I[ib_date] < force_read_threshold) {
    I[ib_read_state] = 1;
  }
  if (L[ib_title] == 2 && !strcmp (S[ib_title], "\\N")) {
    L[ib_title] = 3;
    strcpy (S[ib_title], "...");
  }
  if (L[ib_message] == 2 && !strcmp (S[ib_message], "\\N")) {
    L[ib_message] = 0;
    S[ib_message][0] = 0;
  }
  struct lev_add_message *E = write_alloc (sizeof (struct lev_add_message) + L[ib_title] + L[ib_message] + 2);
  E->type = LEV_TX_ADD_MESSAGE + (I[ib_read_state] ? 0 : TXF_UNREAD) + (I[ib_to_shown] ? TXF_SPAM : 0) + (is_friend (list_id, user_id) ? TXF_FRIENDS : 0);
  E->user_id = list_id;
  E->legacy_id = I[ib_id];
  E->peer_id = user_id;
  E->peer_msg_id = (I[ib_read_state] ? 0 : -I[ib_read_date]);
  E->date = I[ib_date];
  E->ip = I[ib_ip];
  E->port = I[ib_port];
  E->front = I[ib_front];
  E->ua_hash = strtoull (S[ib_ua_hash], 0, 10);
  E->text_len = L[ib_title] + 1 + L[ib_message];
  ptr = E->text;
  len = L[ib_title];
  str = S[ib_title];
  for (i = 0; i < len; i++) {
    if ((unsigned char) str[i] < ' ') {
      *ptr++ = ' ';
    } else {
      *ptr++ = str[i];
    }
  }
  *ptr++ = 9;
  len = L[ib_message];
  str = S[ib_message];
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