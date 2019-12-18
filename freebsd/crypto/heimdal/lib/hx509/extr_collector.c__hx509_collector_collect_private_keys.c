#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t len; TYPE_1__** data; } ;
struct hx509_collector {TYPE_2__ val; } ;
typedef  int /*<<< orphan*/ * hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_3__ {int /*<<< orphan*/ * private_key; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ ** calloc (size_t,int) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

int
_hx509_collector_collect_private_keys(hx509_context context,
				      struct hx509_collector *c,
				      hx509_private_key **keys)
{
    size_t i, nkeys;

    *keys = NULL;

    for (i = 0, nkeys = 0; i < c->val.len; i++)
	if (c->val.data[i]->private_key)
	    nkeys++;

    *keys = calloc(nkeys + 1, sizeof(**keys));
    if (*keys == NULL) {
	hx509_set_error_string(context, 0, ENOMEM, "malloc - out of memory");
	return ENOMEM;
    }

    for (i = 0, nkeys = 0; i < c->val.len; i++) {
 	if (c->val.data[i]->private_key) {
	    (*keys)[nkeys++] = c->val.data[i]->private_key;
	    c->val.data[i]->private_key = NULL;
	}
    }
    (*keys)[nkeys] = NULL;

    return 0;
}