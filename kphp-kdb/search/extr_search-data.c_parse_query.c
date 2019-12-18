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

/* Variables and functions */
 scalar_t__ Q_extmode ; 
 scalar_t__ Q_nodes ; 
 scalar_t__ Q_root ; 
 scalar_t__ Q_words ; 
 scalar_t__ optimize_query (scalar_t__) ; 
 char* parse_ptr ; 
 scalar_t__ parse_query_expr () ; 
 char* parse_query_words (char*) ; 
 char* parse_ranges (char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,scalar_t__,scalar_t__) ; 

char *parse_query (char *text, int do_parse_ranges) {
  Q_words = Q_nodes = 0;
  Q_root = 0;

  if (do_parse_ranges) {
    text = parse_ranges (text);
  }

  if (Q_extmode) {
    parse_ptr = text;

    Q_root = parse_query_expr ();
    if (!Q_root || *parse_ptr) {
      return parse_ptr;
    }

    Q_root = optimize_query (Q_root);
    if (!Q_root) {
      return parse_ptr;
    }

    vkprintf (2, "successfully compiled extended query, %d nodes used, root=%p\n", Q_nodes, Q_root);

    return 0;
  }
  text = parse_query_words (text);

  return 0;
}