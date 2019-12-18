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
typedef  int /*<<< orphan*/  searchy_query_t ;

/* Variables and functions */
 int searchy_parse_phrase0 (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static int searchy_parse_phrase (searchy_query_t *Q, char *text, int text_len, int quot_type, int minus) {
  char *wptr = text + text_len;
  const char old_char = *wptr;
  *wptr = 0;
  int res = searchy_parse_phrase0 (Q, text, quot_type, minus);
  *wptr = old_char;
  return res;
}