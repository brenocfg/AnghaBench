#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {int used; size_t desc; scalar_t__ len; int /*<<< orphan*/  token_q; struct TYPE_7__* data; } ;
typedef  TYPE_1__ au_record_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 size_t MAX_AUDIT_RECORDS ; 
 int MAX_AUDIT_RECORD_SIZE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  au_rec_q ; 
 int /*<<< orphan*/  audit_free_q ; 
 size_t audit_rec_count ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex ; 
 TYPE_1__** open_desc_table ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int
au_open(void)
{
	au_record_t *rec = NULL;

#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_lock(&mutex);
#endif

	if (audit_rec_count == 0)
		LIST_INIT(&audit_free_q);

	/*
	 * Find an unused descriptor, remove it from the free list, mark as
	 * used.
	 */
	if (!LIST_EMPTY(&audit_free_q)) {
		rec = LIST_FIRST(&audit_free_q);
		rec->used = 1;
		LIST_REMOVE(rec, au_rec_q);
	}

#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_unlock(&mutex);
#endif

	if (rec == NULL) {
		/*
		 * Create a new au_record_t if no descriptors are available.
		 */
		rec = malloc (sizeof(au_record_t));
		if (rec == NULL)
			return (-1);

		rec->data = malloc (MAX_AUDIT_RECORD_SIZE * sizeof(u_char));
		if (rec->data == NULL) {
			free(rec);
			errno = ENOMEM;
			return (-1);
		}

#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_lock(&mutex);
#endif

		if (audit_rec_count == MAX_AUDIT_RECORDS) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
			pthread_mutex_unlock(&mutex);
#endif
			free(rec->data);
			free(rec);

			/* XXX We need to increase size of MAX_AUDIT_RECORDS */
			errno = ENOMEM;
			return (-1);
		}
		rec->desc = audit_rec_count;
		open_desc_table[audit_rec_count] = rec;
		audit_rec_count++;

#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif

	}

	memset(rec->data, 0, MAX_AUDIT_RECORD_SIZE);

	TAILQ_INIT(&rec->token_q);
	rec->len = 0;
	rec->used = 1;

	return (rec->desc);
}