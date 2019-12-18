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
struct evkeyvalq {int dummy; } ;
struct evkeyval {struct evkeyval* value; struct evkeyval* key; } ;

/* Variables and functions */
 struct evkeyval* TAILQ_FIRST (struct evkeyvalq*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct evkeyvalq*,struct evkeyval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_free (struct evkeyval*) ; 
 int /*<<< orphan*/  next ; 

void
evhttp_clear_headers(struct evkeyvalq *headers)
{
	struct evkeyval *header;

	for (header = TAILQ_FIRST(headers);
	    header != NULL;
	    header = TAILQ_FIRST(headers)) {
		TAILQ_REMOVE(headers, header, next);
		mm_free(header->key);
		mm_free(header->value);
		mm_free(header);
	}
}