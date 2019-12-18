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
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  TYPE_1__* krb5_context ;
struct TYPE_5__ {int num_kt_types; int /*<<< orphan*/ * kt_types; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  krb5_set_error_message (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static krb5_error_code
kt_ops_copy(krb5_context context, const krb5_context src_context)
{
    context->num_kt_types = 0;
    context->kt_types     = NULL;

    if (src_context->num_kt_types == 0)
	return 0;

    context->kt_types = malloc(sizeof(context->kt_types[0]) * src_context->num_kt_types);
    if (context->kt_types == NULL) {
	krb5_set_error_message(context, ENOMEM,
			       N_("malloc: out of memory", ""));
	return ENOMEM;
    }

    context->num_kt_types = src_context->num_kt_types;
    memcpy(context->kt_types, src_context->kt_types,
	   sizeof(context->kt_types[0]) * src_context->num_kt_types);

    return 0;
}