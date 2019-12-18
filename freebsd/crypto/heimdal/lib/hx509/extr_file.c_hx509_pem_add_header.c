#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* header; int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ hx509_pem_header ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 void* strdup (char const*) ; 

int
hx509_pem_add_header(hx509_pem_header **headers,
		     const char *header, const char *value)
{
    hx509_pem_header *h;

    h = calloc(1, sizeof(*h));
    if (h == NULL)
	return ENOMEM;
    h->header = strdup(header);
    if (h->header == NULL) {
	free(h);
	return ENOMEM;
    }
    h->value = strdup(value);
    if (h->value == NULL) {
	free(h->header);
	free(h);
	return ENOMEM;
    }

    h->next = *headers;
    *headers = h;

    return 0;
}