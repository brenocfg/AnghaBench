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
struct search_index_header {scalar_t__ command_line_switches_flags; scalar_t__ stemmer_version; scalar_t__ word_split_version; scalar_t__ listcomp_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_listcomp_version (scalar_t__) ; 
 scalar_t__ get_cls_flags () ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ listcomp_version ; 
 scalar_t__ stemmer_version ; 
 scalar_t__ word_split_version ; 

int check_header (struct search_index_header *H) {
  if (H->command_line_switches_flags != get_cls_flags ()) {
    kprintf ("Index header command line switches not equal given command line switches. Index flags %08x, current flags %08x\n", H->command_line_switches_flags, get_cls_flags ());
    return 0;
  }
  if (H->stemmer_version != stemmer_version) {
    kprintf ("Header stemmer version = %d, stemmer_version = %d\n", H->stemmer_version, stemmer_version);
    return 0;
  }
  if (H->word_split_version != word_split_version) {
    kprintf ("Header word split version = %d, word split version = %d\n", H->word_split_version, word_split_version);
    return 0;
  }
  if (!check_listcomp_version (H->listcomp_version)) {
    kprintf ("Header listcomp version = %x, listcomp version = %x\n", H->listcomp_version, listcomp_version);
    return 0;
  }
  return 1;
}