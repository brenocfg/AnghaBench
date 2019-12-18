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
struct TYPE_5__ {int /*<<< orphan*/  hostname; int /*<<< orphan*/ * next; int /*<<< orphan*/ * ai; int /*<<< orphan*/  def_port; int /*<<< orphan*/  port; int /*<<< orphan*/  proto; } ;
typedef  TYPE_1__ krb5_krbhst_info ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

krb5_error_code
_krb5_krbhost_info_move(krb5_context context,
			krb5_krbhst_info *from,
			krb5_krbhst_info **to)
{
    size_t hostnamelen = strlen(from->hostname);
    /* trailing NUL is included in structure */
    *to = calloc(1, sizeof(**to) + hostnamelen);
    if(*to == NULL) {
	krb5_set_error_message(context, ENOMEM,
			       N_("malloc: out of memory", ""));
	return ENOMEM;
    }

    (*to)->proto = from->proto;
    (*to)->port = from->port;
    (*to)->def_port = from->def_port;
    (*to)->ai = from->ai;
    from->ai = NULL;
    (*to)->next = NULL;
    memcpy((*to)->hostname, from->hostname, hostnamelen + 1);
    return 0;
}