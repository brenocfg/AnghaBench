#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct treespace_header {int /*<<< orphan*/  used_ints; } ;
struct TYPE_2__ {scalar_t__ data_end; scalar_t__ stale_ads_data_offset; scalar_t__ stale_ads_directory_offset; scalar_t__ fresh_ads_data_offset; scalar_t__ fresh_ads_directory_offset; scalar_t__ word_data_offset; scalar_t__ user_data_offset; scalar_t__ word_directory_offset; } ;

/* Variables and functions */
 scalar_t__ AdSpace ; 
 TYPE_1__ NewHeader ; 
 scalar_t__ WordSpace ; 
 int ancient_ads_loaded ; 
 int /*<<< orphan*/  ancient_ads_loaded_bytes ; 
 double binlog_load_time ; 
 scalar_t__ dyn_cur ; 
 scalar_t__ dyn_first ; 
 scalar_t__ dyn_last ; 
 scalar_t__ dyn_top ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double,...) ; 
 double idx_end_time ; 
 double idx_start_time ; 
 int /*<<< orphan*/  log_cur_pos () ; 
 int /*<<< orphan*/  log_last_ts ; 
 int max_uid ; 
 int new_fresh_ads ; 
 int new_idx_words ; 
 int new_idx_words_short ; 
 int new_stale_ads ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tot_fresh_ads_userlist_bytes ; 
 int /*<<< orphan*/  tot_stale_ads_userlist_bytes ; 
 int /*<<< orphan*/  tot_userlists ; 
 int tot_userlists_size ; 
 int tot_users ; 
 int /*<<< orphan*/  word_user_pairs ; 

__attribute__((used)) static void output_index_stats (void) {
  fprintf (stderr, "binlog loaded in %.3f seconds, binlog position %lld, timestamp %d\n", binlog_load_time, log_cur_pos (), log_last_ts);
  fprintf (stderr, "word directory: %d words, %lld bytes, %d short words\n", new_idx_words, NewHeader.user_data_offset - NewHeader.word_directory_offset, new_idx_words_short);
  fprintf (stderr, "user data: %d users, max_uid=%d, %lld bytes\n", tot_users, max_uid, NewHeader.word_data_offset - NewHeader.user_data_offset);
  fprintf (stderr, "word data: %d words, %lld bytes, %lld word-user pairs\n", new_idx_words - new_idx_words_short, NewHeader.fresh_ads_directory_offset - NewHeader.word_data_offset, word_user_pairs);
  fprintf (stderr, "fresh ads: %d ads, %lld bytes in directory, %lld ad info bytes (%lld of them in userlists)\n", new_fresh_ads, NewHeader.stale_ads_directory_offset - NewHeader.fresh_ads_directory_offset, NewHeader.stale_ads_data_offset - NewHeader.fresh_ads_data_offset, tot_fresh_ads_userlist_bytes);
  fprintf (stderr, "stale ads: %d ads, %lld bytes in directory, %lld ad info bytes (%lld of them in userlists)\n", new_stale_ads, NewHeader.fresh_ads_data_offset - NewHeader.stale_ads_directory_offset, NewHeader.data_end - NewHeader.stale_ads_data_offset, tot_stale_ads_userlist_bytes);
  fprintf (stderr, "loaded %d ancient ads, %lld bytes\n", ancient_ads_loaded, ancient_ads_loaded_bytes);
  fprintf (stderr, "total index size %lld bytes\n", NewHeader.data_end);
  fprintf (stderr, "index generated in %.3f seconds, used %ld dyn_heap bytes, %lld heap bytes for %d userlists, %d+%d treespace ints\n", idx_end_time - idx_start_time, (long) (dyn_cur - dyn_first + dyn_last - dyn_top), tot_userlists_size << 2, tot_userlists, ((struct treespace_header *)AdSpace)->used_ints, ((struct treespace_header *)WordSpace)->used_ints);
}