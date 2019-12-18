#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int phrases_cnt; int words; struct TYPE_4__* words_buf; struct TYPE_4__* phrases; } ;
typedef  TYPE_1__ watchcat_query_t ;
typedef  int /*<<< orphan*/  watchcat_query_phrase_t ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  dl_free (TYPE_1__*,int) ; 

void free_watchcat_query (watchcat_query_t *to) {
  dl_free (to->phrases, sizeof (watchcat_query_phrase_t) * to->phrases_cnt);
  dl_free (to->words_buf, sizeof (hash_t) * to->words);
  dl_free (to, sizeof (watchcat_query_t));
}