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
struct item {char* str; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char*) ; 
 int deleted_text_bytes ; 
 struct item* get_item_f (long long,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  zzfree (char const*,int) ; 
 char* zzmalloc (int) ; 

__attribute__((used)) static int add_item_tags (const char *text, int len, long long item_id) {
  struct item *I = get_item_f (item_id, 1);
  if (I == NULL) {
    return 0;
  }
  assert (I->str);
  int new_len = I->len + len + 1;
  char *s = zzmalloc (new_len + 1);
  assert (s);
  strcpy (s, text);
  s[len] = ' ';
  strcpy (s + len + 1, I->str);
  zzfree (I->str, I->len+1);
  deleted_text_bytes += I->len;
  I->len = new_len;
  I->str = s;
  return 1;
}