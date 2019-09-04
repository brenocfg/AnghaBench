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
 scalar_t__ cur_wordlist_head ; 
 scalar_t__ cur_wordlist_size ; 

__attribute__((used)) static void clear_cur_wordlist (void) {
  cur_wordlist_size = 0;
  cur_wordlist_head = 0;
}