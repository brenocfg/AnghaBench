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
struct mem_data {int /*<<< orphan*/ ** keys; } ;
typedef  int /*<<< orphan*/  hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * _hx509_private_key_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 void* realloc (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static int
mem_addkey(hx509_context context,
	   hx509_certs certs,
	   void *data,
	   hx509_private_key key)
{
    struct mem_data *mem = data;
    void *ptr;
    int i;

    for (i = 0; mem->keys && mem->keys[i]; i++)
	;
    ptr = realloc(mem->keys, (i + 2) * sizeof(*mem->keys));
    if (ptr == NULL) {
	hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	return ENOMEM;
    }
    mem->keys = ptr;
    mem->keys[i] = _hx509_private_key_ref(key);
    mem->keys[i + 1] = NULL;
    return 0;
}