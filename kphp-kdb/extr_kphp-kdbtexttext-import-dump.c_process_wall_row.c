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
 scalar_t__ LEV_TX_ADD_MESSAGE_MF ; 
 char** S ; 
 int TXFS_MEDIA ; 
 int /*<<< orphan*/  TXFS_SPAM ; 
 scalar_t__ TXFS_WALL ; 
 int /*<<< orphan*/  adj_rec ; 
 int check_wall_embedded_media (char*,int) ; 
 scalar_t__ conv_uid (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int list_id ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strtoull (char*,int /*<<< orphan*/ ,int) ; 
 int verbosity ; 
 size_t wa_date ; 
 size_t wa_from_id ; 
 size_t wa_front ; 
 size_t wa_hash ; 
 size_t wa_id ; 
 size_t wa_ip ; 
 size_t wa_message ; 
 size_t wa_port ; 
 size_t wa_to_id ; 
 size_t wa_to_shown ; 
 struct lev_add_message* write_alloc (int) ; 

void process_wall_row (void) {
  int user_id = I[wa_from_id];
  int i, len, has_media = 0;
  char *ptr, *str;
  list_id = I[wa_to_id]; 
  if (conv_uid (list_id) < 0 || !list_id || user_id <= 0) {
    return;
  }
  if (L[wa_message] == 2 && !strcmp (S[wa_message], "\\N")) {
    L[wa_message] = 0;
    S[wa_message][0] = 0;
  }
  if (L[wa_message] >= 5 && S[wa_message][0] == '[' && S[wa_message][1] == '[') {
    has_media = check_wall_embedded_media (S[wa_message], L[wa_message]);
    if (verbosity > 2 && !has_media) {
      fprintf (stderr, "has_media=%d for '%s'\n", has_media, S[wa_message]);
    }
  }
  struct lev_add_message *E = write_alloc (sizeof (struct lev_add_message) + L[wa_message] + 1);
  E->type = (has_media ? LEV_TX_ADD_MESSAGE_MF + has_media * TXFS_MEDIA : LEV_TX_ADD_MESSAGE) + 
            TXFS_WALL + (I[wa_to_shown] ? TXFS_SPAM : 0);
  E->user_id = list_id;
  E->legacy_id = I[wa_id];
  E->peer_id = (user_id == list_id ? (int) 2e9 : user_id);
  E->peer_msg_id = 0;
  E->date = I[wa_date];
  E->ip = I[wa_ip];
  E->port = I[wa_port];
  E->front = I[wa_front];
  E->ua_hash = strtoull (S[wa_hash], 0, 10);
  E->text_len = len = L[wa_message];
  ptr = E->text;
  str = S[wa_message];
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