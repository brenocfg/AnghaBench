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
struct TYPE_7__ {int /*<<< orphan*/  left_subtree_size_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM_GET_MEMORY_USAGE_SELF ; 
 int /*<<< orphan*/  FullVersionStr ; 
 TYPE_5__ Header ; 
 int /*<<< orphan*/  SB_BINLOG ; 
 int /*<<< orphan*/  SB_INDEX ; 
 int /*<<< orphan*/  SB_PRINT_I32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_PRINT_I64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_PRINT_QUERIES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATS_BUFF_SIZE ; 
 int /*<<< orphan*/  alloc_tree_nodes ; 
 int /*<<< orphan*/  creation_date ; 
 int /*<<< orphan*/  decoder_positions_max_capacity ; 
 int /*<<< orphan*/  del_items ; 
 int /*<<< orphan*/  delete_item_queries ; 
 int /*<<< orphan*/  free_tree_nodes ; 
 int /*<<< orphan*/  get_malloc_memory_used () ; 
 int /*<<< orphan*/  hashtags_enabled ; 
 int /*<<< orphan*/  idx_bytes ; 
 int /*<<< orphan*/  idx_items ; 
 int /*<<< orphan*/  idx_words ; 
 int /*<<< orphan*/  increment_queries ; 
 int /*<<< orphan*/  listcomp_version ; 
 int /*<<< orphan*/  max_search_query_memory ; 
 int /*<<< orphan*/  mod_items ; 
 int /*<<< orphan*/  sb_memory (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_prepare (TYPE_1__*,struct connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_printf (TYPE_1__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  search_queries ; 
 int /*<<< orphan*/  set_item_queries ; 
 int /*<<< orphan*/  set_rate_queries ; 
 int /*<<< orphan*/  stats_buff ; 
 int /*<<< orphan*/  stemmer_version ; 
 int /*<<< orphan*/  tag_owner ; 
 int /*<<< orphan*/  tot_freed_deleted_items ; 
 int /*<<< orphan*/  tot_items ; 
 int /*<<< orphan*/  tree_positions_bytes ; 
 int /*<<< orphan*/  universal ; 
 int /*<<< orphan*/  use_stemmer ; 
 int /*<<< orphan*/  word_split_utf8 ; 
 int /*<<< orphan*/  word_split_version ; 
 int /*<<< orphan*/  wordfreqs_enabled ; 

int searchy_prepare_stats (struct connection *c) {
  stats_buffer_t sb;
  sb_prepare (&sb, c, stats_buff, STATS_BUFF_SIZE);
  sb_memory (&sb, AM_GET_MEMORY_USAGE_SELF);
  sb_printf (&sb, "malloc_memory_used\t%lld\n", get_malloc_memory_used ());
  SB_BINLOG;
  SB_INDEX;
  sb_printf (&sb,
    "index_items\t%d\n"
    "index_words\t%d\n"
    "index_data_bytes\t%lld\n",
    idx_items, idx_words, idx_bytes);

  sb_printf (&sb, "left_subtree_size_threshold\t%d\n", Header.left_subtree_size_threshold);
  SB_PRINT_QUERIES(search_queries);
  SB_PRINT_QUERIES(increment_queries);
  SB_PRINT_QUERIES(set_rate_queries);
  SB_PRINT_QUERIES(delete_item_queries);
  SB_PRINT_QUERIES(set_item_queries);

  sb_printf (&sb,
      "items\t%d\n"
      "items_marked_as_deleted\t%d\n"
      "items_freed\t%d\n"
      "index_items_deleted\t%d\n"
      "tree_nodes_allocated\t%d\n"
      "tree_nodes_unused\t%d\n",
    tot_items,
    del_items,
    tot_freed_deleted_items,
    mod_items,
    alloc_tree_nodes,
    free_tree_nodes);

  SB_PRINT_I64(tree_positions_bytes);
  SB_PRINT_I32(decoder_positions_max_capacity);
  SB_PRINT_I32(max_search_query_memory);
  SB_PRINT_I32(use_stemmer);
  SB_PRINT_I32(universal);
  SB_PRINT_I32(hashtags_enabled);
  SB_PRINT_I32(wordfreqs_enabled);
  SB_PRINT_I32(stemmer_version);
  SB_PRINT_I32(word_split_version);
  SB_PRINT_I32(word_split_utf8);
  SB_PRINT_I32(tag_owner);
  SB_PRINT_I32(listcomp_version);
  SB_PRINT_I32(creation_date);

  sb_printf (&sb, "version\t%s\n", FullVersionStr);

  return sb.pos;
}