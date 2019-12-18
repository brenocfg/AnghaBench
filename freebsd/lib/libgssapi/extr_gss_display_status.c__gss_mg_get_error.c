#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ length; int /*<<< orphan*/  value; } ;
struct TYPE_5__ {scalar_t__ length; int /*<<< orphan*/  value; } ;
struct mg_thread_ctx {int maj_stat; int min_stat; TYPE_2__ min_error; TYPE_1__ maj_error; int /*<<< orphan*/  mech; } ;
typedef  TYPE_3__* gss_buffer_t ;
typedef  int /*<<< orphan*/ * gss_OID ;
struct TYPE_7__ {scalar_t__ length; int /*<<< orphan*/ * value; } ;
typedef  int OM_uint32 ;

/* Variables and functions */
#define  GSS_C_GSS_CODE 129 
#define  GSS_C_MECH_CODE 128 
 int GSS_S_BAD_STATUS ; 
 int GSS_S_COMPLETE ; 
 scalar_t__ gss_oid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ * const) ; 
 struct mg_thread_ctx last_error_context ; 
 void* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static OM_uint32
_gss_mg_get_error(const gss_OID mech, OM_uint32 type,
		  OM_uint32 value, gss_buffer_t string)
{
	struct mg_thread_ctx *mg;

	mg = &last_error_context;

	if (mech != NULL && gss_oid_equal(mg->mech, mech) == 0)
		return (GSS_S_BAD_STATUS);

	switch (type) {
	case GSS_C_GSS_CODE: {
		if (value != mg->maj_stat || mg->maj_error.length == 0)
			break;
		string->value = malloc(mg->maj_error.length);
		string->length = mg->maj_error.length;
		memcpy(string->value, mg->maj_error.value,
		    mg->maj_error.length);
		return (GSS_S_COMPLETE);
	}
	case GSS_C_MECH_CODE: {
		if (value != mg->min_stat || mg->min_error.length == 0)
			break;
		string->value = malloc(mg->min_error.length);
		string->length = mg->min_error.length;
		memcpy(string->value, mg->min_error.value,
		    mg->min_error.length);
		return (GSS_S_COMPLETE);
	}
	}
	string->value = NULL;
	string->length = 0;
	return (GSS_S_BAD_STATUS);
}