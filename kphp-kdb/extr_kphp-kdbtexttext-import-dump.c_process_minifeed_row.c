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
struct lev_add_message {int peer_id; int text_len; char* text; scalar_t__ ua_hash; scalar_t__ front; scalar_t__ port; scalar_t__ ip; scalar_t__ date; scalar_t__ peer_msg_id; scalar_t__ legacy_id; scalar_t__ user_id; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__* I ; 
 int* L ; 
 scalar_t__ LEV_TX_ADD_MESSAGE ; 
 scalar_t__ LEV_TX_ADD_MESSAGE_MF ; 
 char** S ; 
 scalar_t__ TXFS_SMS ; 
 int /*<<< orphan*/  adj_rec ; 
 scalar_t__ conv_uid (scalar_t__) ; 
 scalar_t__ list_id ; 
 size_t st_created ; 
 size_t st_id ; 
 size_t st_item_text ; 
 size_t st_user_id ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 struct lev_add_message* write_alloc (int) ; 

void process_minifeed_row (void) {
  int i, len, skip = 0;
  char *ptr, *str;
  list_id = I[st_user_id]; 
  if (conv_uid (list_id) < 0 || list_id <= 0) {
    return;
  }
  if (L[st_item_text] == 2 && !strcmp (S[st_item_text], "\\N")) {
    L[st_item_text] = 0;
    S[st_item_text][0] = 0;
  }
  if (L[st_item_text] <= 2 && !I[st_created]) {
    return;
  }
  skip = (S[st_item_text][0] == ' ');
  struct lev_add_message *E = write_alloc (sizeof (struct lev_add_message) + L[st_item_text] + 1 - skip);
  E->type = (skip ? LEV_TX_ADD_MESSAGE_MF + TXFS_SMS : LEV_TX_ADD_MESSAGE);
  E->user_id = list_id;
  E->legacy_id = I[st_id];
  E->peer_id = (int) 2e9;
  E->peer_msg_id = 0;
  E->date = I[st_created];
  E->ip = 0;
  E->port = 0;
  E->front = 0;
  E->ua_hash = 0;
  E->text_len = len = L[st_item_text] - skip;
  ptr = E->text;
  str = S[st_item_text] + skip;
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