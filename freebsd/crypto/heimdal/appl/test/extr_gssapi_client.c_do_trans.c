#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_8__ {int length; char* value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 scalar_t__ GSS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_err (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gss_get_mic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  write_token (int,TYPE_1__*) ; 

__attribute__((used)) static int
do_trans (int sock, gss_ctx_id_t context_hdl)
{
    OM_uint32 maj_stat, min_stat;
    gss_buffer_desc real_input_token, real_output_token;
    gss_buffer_t input_token = &real_input_token,
	output_token = &real_output_token;

    /* get_mic */

    input_token->length = 3;
    input_token->value  = strdup("hej");

    maj_stat = gss_get_mic(&min_stat,
			   context_hdl,
			   GSS_C_QOP_DEFAULT,
			   input_token,
			   output_token);
    if (GSS_ERROR(maj_stat))
	gss_err (1, min_stat, "gss_get_mic");

    write_token (sock, input_token);
    write_token (sock, output_token);

    /* wrap */

    input_token->length = 7;
    input_token->value  = "hemligt";

    maj_stat = gss_wrap (&min_stat,
			 context_hdl,
			 0,
			 GSS_C_QOP_DEFAULT,
			 input_token,
			 NULL,
			 output_token);
    if (GSS_ERROR(maj_stat))
	gss_err (1, min_stat, "gss_wrap");

    write_token (sock, output_token);

    maj_stat = gss_wrap (&min_stat,
			 context_hdl,
			 1,
			 GSS_C_QOP_DEFAULT,
			 input_token,
			 NULL,
			 output_token);
    if (GSS_ERROR(maj_stat))
	gss_err (1, min_stat, "gss_wrap");

    write_token (sock, output_token);

    return 0;
}