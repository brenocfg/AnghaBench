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
struct mem_data {scalar_t__* keys; } ;
typedef  int /*<<< orphan*/ * hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * _hx509_private_key_ref (scalar_t__) ; 
 int /*<<< orphan*/ ** calloc (int,int) ; 
 int /*<<< orphan*/  hx509_private_key_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
mem_getkeys(hx509_context context,
	     hx509_certs certs,
	     void *data,
	     hx509_private_key **keys)
{
    struct mem_data *mem = data;
    int i;

    for (i = 0; mem->keys && mem->keys[i]; i++)
	;
    *keys = calloc(i + 1, sizeof(**keys));
    for (i = 0; mem->keys && mem->keys[i]; i++) {
	(*keys)[i] = _hx509_private_key_ref(mem->keys[i]);
	if ((*keys)[i] == NULL) {
	    while (--i >= 0)
		hx509_private_key_free(&(*keys)[i]);
	    hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	    return ENOMEM;
	}
    }
    (*keys)[i] = NULL;
    return 0;
}