#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int krb5uint32 ;
typedef  TYPE_3__* krb5_principal ;
struct TYPE_20__ {int num_db; TYPE_6__** db; } ;
typedef  TYPE_4__ krb5_kdc_configuration ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_3__* krb5_const_principal ;
typedef  int /*<<< orphan*/  hdb_entry_ex ;
struct TYPE_21__ {int hdb_capability_flags; int /*<<< orphan*/  (* hdb_close ) (int /*<<< orphan*/ ,TYPE_6__*) ;int /*<<< orphan*/  (* hdb_fetch_kvno ) (int /*<<< orphan*/ ,TYPE_6__*,TYPE_3__*,unsigned int,unsigned int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* hdb_open ) (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {int len; int /*<<< orphan*/ * val; } ;
struct TYPE_18__ {scalar_t__ name_type; TYPE_1__ name_string; } ;
struct TYPE_19__ {TYPE_2__ name; } ;
typedef  TYPE_6__ HDB ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int HDB_CAP_F_HANDLE_ENTERPRISE_PRINCIPAL ; 
 int /*<<< orphan*/  HDB_ERR_NOENTRY ; 
 unsigned int HDB_F_DECRYPT ; 
 unsigned int HDB_F_KVNO_SPECIFIED ; 
 scalar_t__ KRB5_NT_ENTERPRISE_PRINCIPAL ; 
 int /*<<< orphan*/  KRB5_PARSE_MALFORMED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kdc_log (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  krb5_free_error_message (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,TYPE_3__*) ; 
 char* krb5_get_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_parse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_6__*,TYPE_3__*,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,TYPE_6__*) ; 

krb5_error_code
_kdc_db_fetch(krb5_context context,
	      krb5_kdc_configuration *config,
	      krb5_const_principal principal,
	      unsigned flags,
	      krb5uint32 *kvno_ptr,
	      HDB **db,
	      hdb_entry_ex **h)
{
    hdb_entry_ex *ent;
    krb5_error_code ret = HDB_ERR_NOENTRY;
    int i;
    unsigned kvno = 0;

    if (kvno_ptr) {
	    kvno = *kvno_ptr;
	    flags |= HDB_F_KVNO_SPECIFIED;
    }

    ent = calloc (1, sizeof (*ent));
    if (ent == NULL) {
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }

    for(i = 0; i < config->num_db; i++) {
	krb5_principal enterprise_principal = NULL;
	if (!(config->db[i]->hdb_capability_flags & HDB_CAP_F_HANDLE_ENTERPRISE_PRINCIPAL)
	    && principal->name.name_type == KRB5_NT_ENTERPRISE_PRINCIPAL) {
	    if (principal->name.name_string.len != 1) {
		ret = KRB5_PARSE_MALFORMED;
		krb5_set_error_message(context, ret,
				       "malformed request: "
				       "enterprise name with %d name components",
				       principal->name.name_string.len);
		free(ent);
		return ret;
	    }
	    ret = krb5_parse_name(context, principal->name.name_string.val[0],
				  &enterprise_principal);
	    if (ret) {
		free(ent);
		return ret;
	    }

	    principal = enterprise_principal;
	}

	ret = config->db[i]->hdb_open(context, config->db[i], O_RDONLY, 0);
	if (ret) {
	    const char *msg = krb5_get_error_message(context, ret);
	    kdc_log(context, config, 0, "Failed to open database: %s", msg);
	    krb5_free_error_message(context, msg);
	    continue;
	}

	ret = config->db[i]->hdb_fetch_kvno(context,
					    config->db[i],
					    principal,
					    flags | HDB_F_DECRYPT,
					    kvno,
					    ent);

	krb5_free_principal(context, enterprise_principal);

	config->db[i]->hdb_close(context, config->db[i]);
	if(ret == 0) {
	    if (db)
		*db = config->db[i];
	    *h = ent;
	    return 0;
	}
    }
    free(ent);
    krb5_set_error_message(context, ret,
			   "no such entry found in hdb");
    return ret;
}