#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* value; struct TYPE_3__* next; int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ hx509_pem_header ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

const char *
hx509_pem_find_header(const hx509_pem_header *h, const char *header)
{
    while(h) {
	if (strcmp(header, h->header) == 0)
	    return h->value;
	h = h->next;
    }
    return NULL;
}