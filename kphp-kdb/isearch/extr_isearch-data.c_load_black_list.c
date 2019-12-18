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
typedef  int /*<<< orphan*/  trie_arr_node ;

/* Variables and functions */
 int MAX_BUFF ; 
 int /*<<< orphan*/  aho_black_list ; 
 int /*<<< orphan*/  aho_black_list_size ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  black_list ; 
 int /*<<< orphan*/  black_list_set_string (char*,int /*<<< orphan*/ ) ; 
 char* buff ; 
 int /*<<< orphan*/  dl_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  trie_arr_aho (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trie_encode (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int verbosity ; 

void load_black_list (int size) {
  assert (size + 1 < MAX_BUFF);

  int r = read (fd[0], buff, size);
  if (verbosity > 1) {
    fprintf (stderr, "black list read %d\n", size);
  }
  if (r != size) {
    fprintf (stderr, "error reading header from index file: read %d bytes instead of %d at position 0: %m\n", r, size);
  }
  assert (r == size);

  buff[size] = 0;

  if (verbosity > 2) {
    fprintf (stderr, "ADD %s\n", buff);
  }
  black_list_set_string (buff, 0);

  aho_black_list_size = trie_encode (black_list, buff, 0);
  trie_arr_aho ((trie_arr_node *)buff);
  aho_black_list = dl_malloc (aho_black_list_size);
  memcpy (aho_black_list, buff, aho_black_list_size);
}