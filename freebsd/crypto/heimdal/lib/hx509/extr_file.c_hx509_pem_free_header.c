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
struct TYPE_4__ {struct TYPE_4__* value; struct TYPE_4__* header; struct TYPE_4__* next; } ;
typedef  TYPE_1__ hx509_pem_header ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
hx509_pem_free_header(hx509_pem_header *headers)
{
    hx509_pem_header *h;
    while (headers) {
	h = headers;
	headers = headers->next;
	free(h->header);
	free(h->value);
	free(h);
    }
}