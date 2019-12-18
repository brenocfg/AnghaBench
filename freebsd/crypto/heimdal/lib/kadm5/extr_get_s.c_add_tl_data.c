#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t tl_data_length; struct TYPE_6__* tl_data_next; int /*<<< orphan*/ * tl_data_contents; int /*<<< orphan*/  tl_data_type; } ;
typedef  TYPE_1__ krb5_tl_data ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;
typedef  TYPE_2__* kadm5_principal_ent_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_7__ {int /*<<< orphan*/  n_tl_data; TYPE_1__* tl_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  _kadm5_error_code (int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static kadm5_ret_t
add_tl_data(kadm5_principal_ent_t ent, int16_t type,
	    const void *data, size_t size)
{
    krb5_tl_data *tl;

    tl = calloc(1, sizeof(*tl));
    if (tl == NULL)
	return _kadm5_error_code(ENOMEM);

    tl->tl_data_type = type;
    tl->tl_data_length = size;
    tl->tl_data_contents = malloc(size);
    if (tl->tl_data_contents == NULL && size != 0) {
	free(tl);
	return _kadm5_error_code(ENOMEM);
    }
    memcpy(tl->tl_data_contents, data, size);

    tl->tl_data_next = ent->tl_data;
    ent->tl_data = tl;
    ent->n_tl_data++;

    return 0;
}