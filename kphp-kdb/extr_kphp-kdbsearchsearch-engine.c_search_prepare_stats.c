#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct connection {int dummy; } ;
struct TYPE_6__ {int pos; } ;
typedef  TYPE_1__ stats_buffer_t ;
struct TYPE_7__ {long long* compression_bytes; int* word_list_compression_methods; int /*<<< orphan*/  left_subtree_size_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM_GET_MEMORY_USAGE_SELF ; 
 int /*<<< orphan*/  FullVersionStr ; 
 TYPE_5__ Header ; 
 int /*<<< orphan*/  SB_BINLOG ; 
 int /*<<< orphan*/  SB_INDEX ; 
 int /*<<< orphan*/  SB_PRINT_I32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_PRINT_I64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_PRINT_QUERIES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_PRINT_TIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATS_BUFF_SIZE ; 
 int /*<<< orphan*/  add_tags_queries ; 
 int /*<<< orphan*/  alloc_tree_nodes ; 
 int /*<<< orphan*/  assign_max_set_rate_calls ; 
 int /*<<< orphan*/  change_many_rates_queries ; 
 int /*<<< orphan*/  change_multiple_rates_set_rate_calls ; 
 int /*<<< orphan*/  creation_date ; 
 int /*<<< orphan*/  del_items ; 
 int /*<<< orphan*/  delete_hash_queries ; 
 int /*<<< orphan*/  delete_hash_query_items ; 
 int /*<<< orphan*/  delete_items_with_hash_queries ; 
 int /*<<< orphan*/  delete_many_rates_mask ; 
 int /*<<< orphan*/  delete_queries ; 
 int /*<<< orphan*/  extended_search_queries ; 
 int /*<<< orphan*/  free_tree_nodes ; 
 int /*<<< orphan*/  get_malloc_memory_used () ; 
 int /*<<< orphan*/  hashlist_assign_max_queries ; 
 int /*<<< orphan*/  hashtags_enabled ; 
 int /*<<< orphan*/  idx_bytes ; 
 int /*<<< orphan*/  idx_hapax_legomena ; 
 int /*<<< orphan*/  idx_items ; 
 int /*<<< orphan*/  idx_items_with_hash ; 
 int /*<<< orphan*/  idx_words ; 
 int /*<<< orphan*/  import_only_mode ; 
 int /*<<< orphan*/  increment_queries ; 
 int /*<<< orphan*/  last_search_query ; 
 int /*<<< orphan*/  list_get_compression_method_description (int) ; 
 int /*<<< orphan*/  listcomp_version ; 
 int /*<<< orphan*/  minor_update_queries ; 
 int /*<<< orphan*/  mod_items ; 
 int /*<<< orphan*/  rebuild_hashmap_calls ; 
 int /*<<< orphan*/  relevance_search_queries ; 
 int /*<<< orphan*/  return_empty_record_on_error ; 
 int /*<<< orphan*/  safe_div (double,long long) ; 
 int /*<<< orphan*/  sb_memory (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_prepare (TYPE_1__*,struct connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_printf (TYPE_1__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  search_queries ; 
 int /*<<< orphan*/  stats_buff ; 
 int /*<<< orphan*/  stemmer_version ; 
 int /*<<< orphan*/  tag_owner ; 
 int /*<<< orphan*/  tot_freed_deleted_items ; 
 int /*<<< orphan*/  tot_items ; 
 int /*<<< orphan*/  universal ; 
 int /*<<< orphan*/  update_queries ; 
 int /*<<< orphan*/  use_stemmer ; 
 int /*<<< orphan*/  word_split_utf8 ; 
 int /*<<< orphan*/  word_split_version ; 
 int /*<<< orphan*/  wordfreqs_enabled ; 
 int /*<<< orphan*/  worst_change_many_rates_time ; 
 int /*<<< orphan*/  worst_delete_items_with_hash_time ; 
 int /*<<< orphan*/  worst_hashlist_assign_max_time ; 

int search_prepare_stats (struct connection *c) {
  stats_buffer_t sb;
  sb_prepare (&sb, c, stats_buff, STATS_BUFF_SIZE);
  sb_memory (&sb, AM_GET_MEMORY_USAGE_SELF);
  sb_printf (&sb, "malloc_memory_used\t%lld\n", get_malloc_memory_used ());
  SB_BINLOG;
  SB_INDEX;
  sb_printf (&sb,
    "index_items\t%d\n"
    "index_words\t%d\n"
    "index_hapax_legomena\t%d\n"
    "index_items_with_hash\t%d\n"
    "index_data_bytes\t%ld\n",
    idx_items, idx_words, idx_hapax_legomena,
    idx_items_with_hash, idx_bytes);

  int k;
  long long golomb_cb = Header.compression_bytes[0] + Header.compression_bytes[1];
  for (k = 0; k < 4; k++) {
    long long t1 = Header.compression_bytes[2*k+0],
              t2 = Header.compression_bytes[2*k+1],
              t = t1 + t2;
    if (t > 0) {
      if (golomb_cb > 0) {
        sb_printf (&sb, "%s\t%lld(%.6lf%%)=%lld(%.6lf%%)+%lld(%.6lf%%)\n",
                       list_get_compression_method_description (k),
                       t, safe_div (100.0 * t, golomb_cb),
                       t1, safe_div (100.0 * t1, Header.compression_bytes[0]),
                       t2, safe_div (100.0 * t2, Header.compression_bytes[1]));
      } else {
        sb_printf (&sb, "%s\t%lld=%lld+%lld\n",
                       list_get_compression_method_description (k),
                       t,
                       t1,
                       t2);
      }
    }
  }

  sb_printf (&sb,
      "index_compression_methods\t%s+%s\n"
      "left_subtree_size_threshold\t%d\n",
    list_get_compression_method_description (Header.word_list_compression_methods[0]),
    list_get_compression_method_description (Header.word_list_compression_methods[1]),
    Header.left_subtree_size_threshold);

  SB_PRINT_QUERIES(search_queries);
  SB_PRINT_QUERIES(extended_search_queries);
  SB_PRINT_QUERIES(relevance_search_queries);
  SB_PRINT_QUERIES(delete_queries);
  SB_PRINT_QUERIES(delete_hash_queries);
  SB_PRINT_QUERIES(update_queries);
  SB_PRINT_QUERIES(minor_update_queries);
  SB_PRINT_QUERIES(increment_queries);
  SB_PRINT_QUERIES(delete_items_with_hash_queries);
  SB_PRINT_QUERIES(hashlist_assign_max_queries);
  SB_PRINT_QUERIES(change_many_rates_queries);
  SB_PRINT_QUERIES(add_tags_queries);
  sb_printf (&sb,
      "items\t%d\n"
      "items_marked_as_deleted\t%d\n"
      "items_freed\t%d\n"
      "index_items_deleted\t%d\n"
      "tree_nodes_allocated\t%d\n"
      "tree_nodes_unused\t%d\n"
      "rebuild_hashmap_calls\t%lld\n"
      "last_search_query\t%s\n",
    tot_items,
    del_items,
    tot_freed_deleted_items,
    mod_items,
    alloc_tree_nodes,
    free_tree_nodes,
    rebuild_hashmap_calls,
    last_search_query);
  SB_PRINT_I64(delete_hash_query_items);
  SB_PRINT_I64(assign_max_set_rate_calls);
  SB_PRINT_I64(change_multiple_rates_set_rate_calls);
  SB_PRINT_TIME(worst_delete_items_with_hash_time);
  SB_PRINT_TIME(worst_hashlist_assign_max_time);
  SB_PRINT_TIME(worst_change_many_rates_time);

  SB_PRINT_I32(use_stemmer);
  SB_PRINT_I32(universal);
  SB_PRINT_I32(hashtags_enabled);
  SB_PRINT_I32(wordfreqs_enabled);
  SB_PRINT_I32(import_only_mode);
  SB_PRINT_I32(stemmer_version);
  SB_PRINT_I32(word_split_version);
  SB_PRINT_I32(word_split_utf8);
  SB_PRINT_I32(tag_owner);
  SB_PRINT_I32(listcomp_version);
  SB_PRINT_I32(creation_date);
  SB_PRINT_I32(delete_many_rates_mask);
  SB_PRINT_I32(return_empty_record_on_error);

  sb_printf (&sb, "version\t%s\n", FullVersionStr);

  return sb.pos;
}