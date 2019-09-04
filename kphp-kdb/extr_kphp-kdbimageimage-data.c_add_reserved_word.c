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
typedef  int /*<<< orphan*/  fpr_t ;

/* Variables and functions */
 int /*<<< orphan*/ * RESERVED_WORDS_F ; 
 int /*<<< orphan*/  assert (int) ; 
 int get_cmd_f (char const*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const*,int) ; 

__attribute__((used)) static int add_reserved_word (const char* cmd, fpr_t f) {
  int i = get_cmd_f (cmd, 1);
  assert (i >= 0);
  RESERVED_WORDS_F[i] = f;
  vkprintf (3, "add_reserved_word %s at slot %d\n", cmd, i);
  return i;
}