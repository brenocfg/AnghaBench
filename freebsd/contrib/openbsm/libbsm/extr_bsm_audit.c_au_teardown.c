#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* t_data; } ;
typedef  TYPE_1__ token_t ;
struct TYPE_9__ {scalar_t__ len; scalar_t__ used; int /*<<< orphan*/  token_q; } ;
typedef  TYPE_2__ au_record_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_rec_q ; 
 int /*<<< orphan*/  audit_free_q ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static void
au_teardown(au_record_t *rec)
{
	token_t *tok;

	/* Free the token list */
	while ((tok = TAILQ_FIRST(&rec->token_q)) != NULL) {
		TAILQ_REMOVE(&rec->token_q, tok, tokens);
		free(tok->t_data);
		free(tok);
	}

	rec->used = 0;
	rec->len = 0;

#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_lock(&mutex);
#endif

	/* Add the record to the freelist tail */
	LIST_INSERT_HEAD(&audit_free_q, rec, au_rec_q);

#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_unlock(&mutex);
#endif
}