#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct targ_index_word_directory_entry {int dummy; } ;
struct hash_word {int word_tree; int word; int num; struct hash_word* next; } ;
typedef  TYPE_1__* iterator_t ;
typedef  int hash_t ;
struct TYPE_9__ {int word; } ;
struct TYPE_8__ {int word; int data_offset; } ;
struct TYPE_7__ {int pos; } ;

/* Variables and functions */
 int HASH_BUCKETS ; 
 struct hash_word** Hash ; 
 int INFTY ; 
 TYPE_2__* NewWordDir ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* build_word_iterator (int) ; 
 int /*<<< orphan*/  clear_tmp_word_data () ; 
 int /*<<< orphan*/  dyn_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 struct hash_word* get_hash_node (int,int /*<<< orphan*/ ) ; 
 int get_idx_word_list_len (int) ; 
 TYPE_4__* idx_worddir ; 
 int idx_words ; 
 TYPE_2__* malloc (int) ; 
 int new_idx_words ; 
 int new_worddir_size ; 
 int /*<<< orphan*/  sort_word_dictionary (TYPE_2__*,int) ; 

void init_new_word_directory (void) {
  int i, j = 0;
  struct hash_word *p;
  for (i = 0; i < HASH_BUCKETS; i++) {
    for (p = Hash[i]; p; p = p->next) {
      if (p->word_tree) {
	++j;
	assert ((unsigned) j < 0x7fffffff / sizeof (struct targ_index_word_directory_entry) - 1);
      }
    }
  }
  new_idx_words = j;
  new_worddir_size = (new_idx_words + idx_words + 1) * sizeof (struct targ_index_word_directory_entry);
  NewWordDir = malloc (new_worddir_size);
  for (i = 0, j = 0; i < HASH_BUCKETS; i++) {
    for (p = Hash[i]; p; p = p->next) {
      if (p->word_tree) {
	clear_tmp_word_data ();
	int ilen = get_idx_word_list_len (p->word);
	if (ilen == p->num) {
	  dyn_mark (0);
	  iterator_t I = build_word_iterator (p->word);
	  int res = I->pos;
	  dyn_release (0);
	  if (res == INFTY) {
	    continue;
	  }
	}
	NewWordDir[j].word = p->word;
	NewWordDir[j].data_offset = p->word_tree;
	++j;
      }
    }
  }
  assert (j <= new_idx_words);

  for (i = 0; i < idx_words; i++) {
    hash_t word = idx_worddir[i].word;
    p = get_hash_node (word, 0);
    if (!p || !p->word_tree) {
      NewWordDir[j].word = word;
      NewWordDir[j].data_offset = 0;
      j++;
    }
  }

  assert (j <= new_idx_words + idx_words);
  new_idx_words = j;

  NewWordDir[j].word = -1;
  NewWordDir[j].data_offset = -1;
  new_worddir_size = (new_idx_words + 1) * sizeof (struct targ_index_word_directory_entry);

  sort_word_dictionary (NewWordDir, j - 1);
}