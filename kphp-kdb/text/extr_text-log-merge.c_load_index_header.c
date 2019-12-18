#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct text_index_header {int dummy; } ;
struct file_user_list_entry {int dummy; } ;
struct file_char_dictionary {int dummy; } ;
struct TYPE_3__ {scalar_t__ magic; int sublists_num; int tot_users; scalar_t__ last_global_id; int sublists_descr_offset; int word_char_dictionary_offset; int notword_char_dictionary_offset; int word_dictionary_offset; int notword_dictionary_offset; int user_list_offset; int user_data_offset; long long extra_data_offset; long long data_end_offset; } ;

/* Variables and functions */
 TYPE_1__ Header ; 
 int MAX_FILE_DICTIONARY_BYTES ; 
 unsigned int MAX_SUBLISTS ; 
 unsigned int MAX_USERS ; 
 scalar_t__ TEXT_INDEX_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int read (int,TYPE_1__*,int) ; 

int load_index_header (int fd, long long fsize) {
  int r;

  r = read (fd, &Header, sizeof (struct text_index_header));
  assert (r == sizeof (struct text_index_header));
  assert (Header.magic == TEXT_INDEX_MAGIC);

  assert ((unsigned) Header.sublists_num <= MAX_SUBLISTS);
  assert ((unsigned) Header.tot_users <= MAX_USERS);
  assert (Header.last_global_id >= 0);


  int userlist_entry_size = sizeof (struct file_user_list_entry) + 4 * Header.sublists_num;

  assert (Header.sublists_descr_offset >= sizeof (struct text_index_header));
  assert (Header.sublists_descr_offset + Header.sublists_num * 4 <= Header.word_char_dictionary_offset);
  assert (Header.word_char_dictionary_offset + sizeof (struct file_char_dictionary) <= Header.notword_char_dictionary_offset);
  assert (Header.notword_char_dictionary_offset + sizeof (struct file_char_dictionary) <= Header.word_dictionary_offset);
  assert (Header.notword_dictionary_offset >= Header.word_dictionary_offset + 4);
  assert (Header.notword_dictionary_offset <= Header.word_dictionary_offset + MAX_FILE_DICTIONARY_BYTES);
  assert (Header.user_list_offset >= Header.notword_dictionary_offset + 4);
  assert (Header.user_list_offset <= Header.notword_dictionary_offset + MAX_FILE_DICTIONARY_BYTES);
//  fprintf (stderr, "user_list_offset=%lld, tot_users=%d, userlist_entry_size=%d, user_data_offset=%lld\n");
  assert (Header.user_list_offset + Header.tot_users * userlist_entry_size + 16 <= Header.user_data_offset);
  assert (Header.user_data_offset <= Header.extra_data_offset);
  assert (Header.extra_data_offset <= Header.data_end_offset);
  assert (Header.data_end_offset == fsize);

  return 0;
}