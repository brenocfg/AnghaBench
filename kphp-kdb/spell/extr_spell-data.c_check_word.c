#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  spell_checker; scalar_t__ russian; int /*<<< orphan*/ ** stat; } ;
struct TYPE_3__ {int /*<<< orphan*/  spell_checker; int /*<<< orphan*/ ** stat; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  AspellWordList ;
typedef  int /*<<< orphan*/  AspellStringEnumeration ;

/* Variables and functions */
 TYPE_2__** SC ; 
 TYPE_1__** SS ; 
 int aspell_speller_check (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  aspell_speller_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * aspell_speller_suggest (int /*<<< orphan*/ ,char*,int) ; 
 char* aspell_string_enumeration_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * aspell_word_list_elements (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  delete_aspell_string_enumeration (int /*<<< orphan*/ *) ; 
 int get_str_class (char const*,int) ; 
 int spellers ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  use_aspell_suggestion ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const*,...) ; 
 scalar_t__ yo_hack ; 
 int /*<<< orphan*/ * yo_hack_stat ; 

int check_word (char *word, int len) {
  int i;
  for (i = 0; i < spellers; i++) {
    int r = aspell_speller_check (SC[i]->spell_checker, word, len);
    if (r >= 0) {
      SC[i]->stat[0][1]++;
      if (r) {
        SC[i]->stat[0][0]++;
        return 1;
      }
    }
  }
  
  if (yo_hack) {
    int j;
    yo_hack_stat[1]++;
    for (j = 0; j < len; j++) {
      if ((unsigned char) word[j] == 0xe5) {
        word[j] = 0xb8;
        for (i = 0; i < spellers; i++) {
          if (SC[i]->russian && aspell_speller_check (SC[i]->spell_checker, word, len) == 1) {            
            word[j] = 0xe5;
            yo_hack_stat[0]++;
            return 1;
          }
        }
        word[j] = 0xe5;
      }
    }
  }

  if (!use_aspell_suggestion) {
    return 0;
  }
  int class = get_str_class (word, len);
  for (i = 0; i < spellers; i++) {
    SS[i]->stat[1][1]++;
    const AspellWordList *suggestions = aspell_speller_suggest (SS[i]->spell_checker, word, len);
    if (suggestions) {
      AspellStringEnumeration *elements = aspell_word_list_elements (suggestions);
      const char *w;
      int words = 0;
      while ( (w = aspell_string_enumeration_next (elements)) != NULL ) {
        vkprintf (3, "suggest: %s, %.*s (%s)\n", w, len, word, SS[i]->name);
        if (class != get_str_class (w, strlen (w))) {
          continue;
        }
        words++;
        break;
      }
      delete_aspell_string_enumeration (elements);
      if (words) {
        SS[i]->stat[1][0]++;
        return 0;
      }
    } else {
      vkprintf (3, "suggetsions = NULL. %s\n", aspell_speller_error_message (SS[i]->spell_checker));
    }
  }
  return -1;
}