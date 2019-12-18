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
struct lev_add_message {int user_id; int legacy_id; int peer_id; int date; int ip; int port; int front; int text_len; char* text; int /*<<< orphan*/  ua_hash; scalar_t__ peer_msg_id; scalar_t__ type; } ;

/* Variables and functions */
 int* I ; 
 int* L ; 
 scalar_t__ LEV_TX_ADD_MESSAGE ; 
 char** S ; 
 int /*<<< orphan*/  TXF_FRIENDS ; 
 scalar_t__ TXF_OUTBOX ; 
 scalar_t__ TXF_UNREAD ; 
 int /*<<< orphan*/  adj_rec ; 
 scalar_t__ conv_uid (int) ; 
 scalar_t__ is_friend (int,int) ; 
 int list_id ; 
 size_t ob_date ; 
 size_t ob_from_id ; 
 size_t ob_front ; 
 size_t ob_id ; 
 size_t ob_ip ; 
 size_t ob_message ; 
 size_t ob_port ; 
 size_t ob_read_state ; 
 size_t ob_title ; 
 size_t ob_to_id ; 
 size_t ob_ua_hash ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strtoull (char*,int /*<<< orphan*/ ,int) ; 
 struct lev_add_message* write_alloc (int) ; 

void process_outbox_row (void) {
  int user_id = I[ob_to_id];
  int i, len;
  char *ptr, *str;
  list_id = I[ob_from_id]; 
  if (conv_uid (list_id) < 0 || list_id <= 0 || user_id <= 0) {
    return;
  }
  if (L[ob_title] == 2 && !strcmp (S[ob_title], "\\N")) {
    L[ob_title] = 3;
    strcpy (S[ob_title], "...");
  }
  if (L[ob_message] == 2 && !strcmp (S[ob_message], "\\N")) {
    L[ob_message] = 0;
    S[ob_message][0] = 0;
  }
  struct lev_add_message *E = write_alloc (sizeof (struct lev_add_message) + L[ob_title] + L[ob_message] + 2);
  E->type = LEV_TX_ADD_MESSAGE + (I[ob_read_state] ? 0 : TXF_UNREAD) + TXF_OUTBOX + (is_friend (list_id, user_id) ? TXF_FRIENDS : 0);
  E->user_id = list_id;
  E->legacy_id = -I[ob_id];
  E->peer_id = user_id;
  E->peer_msg_id = 0;
  E->date = I[ob_date];
  E->ip = I[ob_ip];
  E->port = I[ob_port];
  E->front = I[ob_front];
  E->ua_hash = strtoull (S[ob_ua_hash], 0, 10);
  E->text_len = L[ob_title] + 1 + L[ob_message];
  ptr = E->text;
  len = L[ob_title];
  str = S[ob_title];
  for (i = 0; i < len; i++) {
    if ((unsigned char) str[i] < ' ') {
      *ptr++ = ' ';
    } else {
      *ptr++ = str[i];
    }
  }
  *ptr++ = 9;
  len = L[ob_message];
  str = S[ob_message];
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