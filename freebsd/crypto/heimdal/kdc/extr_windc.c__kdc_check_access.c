#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  hdb_entry_ex ;
struct TYPE_6__ {int /*<<< orphan*/  (* client_access ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {scalar_t__ msg_type; } ;
typedef  TYPE_1__ KDC_REQ ;

/* Variables and functions */
 int /*<<< orphan*/  kdc_check_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ krb_as_req ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  windcctx ; 
 TYPE_2__* windcft ; 

krb5_error_code
_kdc_check_access(krb5_context context,
		  krb5_kdc_configuration *config,
		  hdb_entry_ex *client_ex, const char *client_name,
		  hdb_entry_ex *server_ex, const char *server_name,
		  KDC_REQ *req,
		  krb5_data *e_data)
{
    if (windcft == NULL)
	    return kdc_check_flags(context, config,
				   client_ex, client_name,
				   server_ex, server_name,
				   req->msg_type == krb_as_req);

    return (windcft->client_access)(windcctx,
				    context, config,
				    client_ex, client_name,
				    server_ex, server_name,
				    req, e_data);
}