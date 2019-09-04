#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int words; int phrases_cnt; int /*<<< orphan*/ * phrases; void* words_buf; } ;
typedef  TYPE_1__ watchcat_query_t ;
typedef  int /*<<< orphan*/  watchcat_query_phrase_t ;
struct TYPE_8__ {int words; int /*<<< orphan*/  words_buf; int /*<<< orphan*/ * phrases; } ;
typedef  TYPE_2__ searchy_query_t ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cmp_watchcat_query_phrase ; 
 void* dl_malloc (int) ; 
 TYPE_1__* dl_malloc0 (int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * searchy_phrases_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 int searchy_phrases_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  searchy_query_free (TYPE_2__*) ; 
 int /*<<< orphan*/  searchy_query_parse (TYPE_2__*,char*) ; 

watchcat_query_t *create_watchcat_query (char *s) {
  static searchy_query_t Q;
  searchy_query_parse (&Q, s);

  searchy_query_t *from = &Q;
  watchcat_query_t *to = dl_malloc0 (sizeof (watchcat_query_t));
  to->words = from->words;
  size_t words_size = sizeof (hash_t) * to->words;
  to->words_buf = dl_malloc (words_size);
  memcpy (to->words_buf, from->words_buf, words_size);

  int phrases_cnt_0 = searchy_phrases_length (from->phrases[0]);
  int phrases_cnt_1 = searchy_phrases_length (from->phrases[1]);
  to->phrases_cnt = phrases_cnt_0 + phrases_cnt_1;

  to->phrases = dl_malloc (sizeof (watchcat_query_phrase_t) * to->phrases_cnt);
  watchcat_query_phrase_t *phrase_ptr = to->phrases;
  phrase_ptr = searchy_phrases_dump (
      phrase_ptr, from->phrases[0], 0, to->words_buf, from->words_buf
  );
  phrase_ptr = searchy_phrases_dump (
      phrase_ptr, from->phrases[1], 1, to->words_buf, from->words_buf
  );
  assert (phrase_ptr == to->phrases + to->phrases_cnt);

  qsort (to->phrases, to->phrases_cnt, sizeof (watchcat_query_phrase_t), cmp_watchcat_query_phrase);

  searchy_query_free (&Q);
  return to;
}