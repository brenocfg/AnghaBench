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
 int /*<<< orphan*/  gen_double_eng () ; 
 int /*<<< orphan*/  gen_li_endings_eng () ; 
 int /*<<< orphan*/  gen_syllable_exceptions_eng () ; 
 int /*<<< orphan*/  gen_trie_eng () ; 
 int /*<<< orphan*/  gen_trie_rus () ; 
 int /*<<< orphan*/  gen_vowels_eng () ; 
 int /*<<< orphan*/  gen_vowels_rus () ; 

void stem_init (void) {
  gen_trie_rus ();
  gen_vowels_rus ();

  gen_trie_eng ();
  gen_vowels_eng ();
  gen_double_eng ();
  gen_li_endings_eng ();
  gen_syllable_exceptions_eng ();
}