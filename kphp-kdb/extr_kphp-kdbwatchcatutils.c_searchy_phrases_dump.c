#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int minus_flag; int /*<<< orphan*/  type; int /*<<< orphan*/  words; int /*<<< orphan*/ * H; } ;
typedef  TYPE_1__ watchcat_query_phrase_t ;
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/  type; int /*<<< orphan*/  words; int /*<<< orphan*/ * H; } ;
typedef  TYPE_2__ searchy_query_phrase_t ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */

watchcat_query_phrase_t *searchy_phrases_dump (watchcat_query_phrase_t *dest, searchy_query_phrase_t *cur,
  int minus_flag, hash_t *dest_words_buf, hash_t *src_words_buf) {
  while (cur != NULL) {
    dest->H = dest_words_buf + (cur->H - src_words_buf);
    dest->words = cur->words;
    dest->type = cur->type;
    dest->minus_flag = minus_flag;
    dest++;
    cur = cur->next;
  }
  return dest;
}