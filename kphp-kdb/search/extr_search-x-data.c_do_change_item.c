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
struct lev_search_text_short_entry {int rate2; long long obj_id; char* text; } ;
struct lev_search_text_long_entry {int rate2; long long obj_id; int text_len; char* text; } ;

/* Variables and functions */
 scalar_t__ LEV_SEARCH_TEXT_LONG ; 
 scalar_t__ LEV_SEARCH_TEXT_SHORT ; 
 void* alloc_log_event (scalar_t__,int,int) ; 
 int change_item (char*,int,long long,int,int) ; 
 int /*<<< orphan*/  fits (long long) ; 

int do_change_item (const char *text, int len, long long item_id, int rate, int rate2) {
  char *q;
  int i;
  if (len >= 65536 || len < 0 || !fits (item_id)) {
    return 0;
  }
  if (len < 256) {
    struct lev_search_text_short_entry *LS = alloc_log_event (LEV_SEARCH_TEXT_SHORT+len, 21+len, rate);
    LS->rate2 = rate2;
    LS->obj_id = item_id;
    q = LS->text;
  } else {
    struct lev_search_text_long_entry *LL = alloc_log_event (LEV_SEARCH_TEXT_LONG, 23+len, rate);
    LL->rate2 = rate2;
    LL->obj_id = item_id;
    LL->text_len = len;
    q = LL->text;
  }
  i = 0;
  while (i < len) {
    if (text[i] == 0x1f) {
      do {
        *q++ = text[i++];
      } while (i < len && (unsigned char) text[i] >= 0x40);
    } else if ((unsigned char) text[i] < ' ' && text[i] != 9) {
      *q++ = ' ';
      i++;
    } else {
      *q++ = text[i++];
    }
  }
  *q = 0;
  return change_item (q - len, len, item_id, rate, rate2);
}