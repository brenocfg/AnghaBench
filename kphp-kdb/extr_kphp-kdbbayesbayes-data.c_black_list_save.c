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
typedef  int /*<<< orphan*/  entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int black_list_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  buff ; 
 int /*<<< orphan*/ * fd ; 
 int max_words ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int black_list_save (void) {
  int len = black_list_get (buff, max_words * sizeof (entry_t));
  len++;
  assert (write (fd[1], buff, len) == len);
  return len;
}