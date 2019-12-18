#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  log_ent ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_18__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ krb5_data ;
struct TYPE_19__ {int /*<<< orphan*/  context; TYPE_5__* db; } ;
typedef  TYPE_3__ kadm5_server_context ;
typedef  scalar_t__ kadm5_ret_t ;
typedef  int int32_t ;
struct TYPE_17__ {size_t len; int /*<<< orphan*/ * val; } ;
struct TYPE_16__ {int /*<<< orphan*/ * extensions; TYPE_1__ keys; int /*<<< orphan*/ * max_renew; int /*<<< orphan*/  kvno; int /*<<< orphan*/ * modified_by; int /*<<< orphan*/ * max_life; int /*<<< orphan*/  flags; int /*<<< orphan*/ * pw_end; int /*<<< orphan*/ * valid_end; int /*<<< orphan*/  principal; } ;
struct TYPE_20__ {TYPE_14__ entry; } ;
typedef  TYPE_4__ hdb_entry_ex ;
typedef  int /*<<< orphan*/  ent ;
struct TYPE_21__ {scalar_t__ (* hdb_store ) (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*) ;scalar_t__ (* hdb_fetch_kvno ) (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_4__*) ;} ;
typedef  int /*<<< orphan*/  HDB_extensions ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int HDB_F_ADMIN_DATA ; 
 int HDB_F_DECRYPT ; 
 int HDB_F_GET_ANY ; 
 int /*<<< orphan*/  HDB_F_REPLACE ; 
 int KADM5_ATTRIBUTES ; 
 int KADM5_AUX_ATTRIBUTES ; 
 int KADM5_FAIL_AUTH_COUNT ; 
 int KADM5_KEY_DATA ; 
 int KADM5_KVNO ; 
 int KADM5_LAST_FAILED ; 
 int KADM5_LAST_PWD_CHANGE ; 
 int KADM5_LAST_SUCCESS ; 
 int KADM5_MAX_LIFE ; 
 int KADM5_MAX_RLIFE ; 
 int KADM5_MKVNO ; 
 int KADM5_MOD_NAME ; 
 int KADM5_MOD_TIME ; 
 int KADM5_POLICY ; 
 int KADM5_POLICY_CLR ; 
 int KADM5_PRINC_EXPIRE_TIME ; 
 int KADM5_PW_EXPIRATION ; 
 int KADM5_TL_DATA ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 scalar_t__ copy_Event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ copy_HDB_extensions (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ copy_Key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_Event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_HDB_extensions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_Key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdb_free_entry (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ hdb_value2entry (int /*<<< orphan*/ ,TYPE_2__*,TYPE_14__*) ; 
 scalar_t__ krb5_data_alloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_ret_int32 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_storage_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static kadm5_ret_t
kadm5_log_replay_modify (kadm5_server_context *context,
			 uint32_t ver,
			 uint32_t len,
			 krb5_storage *sp)
{
    krb5_error_code ret;
    int32_t mask;
    krb5_data value;
    hdb_entry_ex ent, log_ent;

    memset(&log_ent, 0, sizeof(log_ent));

    krb5_ret_int32 (sp, &mask);
    len -= 4;
    ret = krb5_data_alloc (&value, len);
    if (ret) {
	krb5_set_error_message(context->context, ret, "out of memory");
	return ret;
    }
    krb5_storage_read (sp, value.data, len);
    ret = hdb_value2entry (context->context, &value, &log_ent.entry);
    krb5_data_free(&value);
    if (ret)
	return ret;

    memset(&ent, 0, sizeof(ent));
    ret = context->db->hdb_fetch_kvno(context->context, context->db,
				      log_ent.entry.principal,
				      HDB_F_DECRYPT|HDB_F_GET_ANY|HDB_F_ADMIN_DATA, 0, &ent);
    if (ret)
	goto out;
    if (mask & KADM5_PRINC_EXPIRE_TIME) {
	if (log_ent.entry.valid_end == NULL) {
	    ent.entry.valid_end = NULL;
	} else {
	    if (ent.entry.valid_end == NULL) {
		ent.entry.valid_end = malloc(sizeof(*ent.entry.valid_end));
		if (ent.entry.valid_end == NULL) {
		    ret = ENOMEM;
		    krb5_set_error_message(context->context, ret, "out of memory");
		    goto out;
		}
	    }
	    *ent.entry.valid_end = *log_ent.entry.valid_end;
	}
    }
    if (mask & KADM5_PW_EXPIRATION) {
	if (log_ent.entry.pw_end == NULL) {
	    ent.entry.pw_end = NULL;
	} else {
	    if (ent.entry.pw_end == NULL) {
		ent.entry.pw_end = malloc(sizeof(*ent.entry.pw_end));
		if (ent.entry.pw_end == NULL) {
		    ret = ENOMEM;
		    krb5_set_error_message(context->context, ret, "out of memory");
		    goto out;
		}
	    }
	    *ent.entry.pw_end = *log_ent.entry.pw_end;
	}
    }
    if (mask & KADM5_LAST_PWD_CHANGE) {
	abort ();		/* XXX */
    }
    if (mask & KADM5_ATTRIBUTES) {
	ent.entry.flags = log_ent.entry.flags;
    }
    if (mask & KADM5_MAX_LIFE) {
	if (log_ent.entry.max_life == NULL) {
	    ent.entry.max_life = NULL;
	} else {
	    if (ent.entry.max_life == NULL) {
		ent.entry.max_life = malloc (sizeof(*ent.entry.max_life));
		if (ent.entry.max_life == NULL) {
		    ret = ENOMEM;
		    krb5_set_error_message(context->context, ret, "out of memory");
		    goto out;
		}
	    }
	    *ent.entry.max_life = *log_ent.entry.max_life;
	}
    }
    if ((mask & KADM5_MOD_TIME) && (mask & KADM5_MOD_NAME)) {
	if (ent.entry.modified_by == NULL) {
	    ent.entry.modified_by = malloc(sizeof(*ent.entry.modified_by));
	    if (ent.entry.modified_by == NULL) {
		ret = ENOMEM;
		krb5_set_error_message(context->context, ret, "out of memory");
		goto out;
	    }
	} else
	    free_Event(ent.entry.modified_by);
	ret = copy_Event(log_ent.entry.modified_by, ent.entry.modified_by);
	if (ret) {
	    krb5_set_error_message(context->context, ret, "out of memory");
	    goto out;
	}
    }
    if (mask & KADM5_KVNO) {
	ent.entry.kvno = log_ent.entry.kvno;
    }
    if (mask & KADM5_MKVNO) {
	abort ();		/* XXX */
    }
    if (mask & KADM5_AUX_ATTRIBUTES) {
	abort ();		/* XXX */
    }
    if (mask & KADM5_POLICY) {
	abort ();		/* XXX */
    }
    if (mask & KADM5_POLICY_CLR) {
	abort ();		/* XXX */
    }
    if (mask & KADM5_MAX_RLIFE) {
	if (log_ent.entry.max_renew == NULL) {
	    ent.entry.max_renew = NULL;
	} else {
	    if (ent.entry.max_renew == NULL) {
		ent.entry.max_renew = malloc (sizeof(*ent.entry.max_renew));
		if (ent.entry.max_renew == NULL) {
		    ret = ENOMEM;
		    krb5_set_error_message(context->context, ret, "out of memory");
		    goto out;
		}
	    }
	    *ent.entry.max_renew = *log_ent.entry.max_renew;
	}
    }
    if (mask & KADM5_LAST_SUCCESS) {
	abort ();		/* XXX */
    }
    if (mask & KADM5_LAST_FAILED) {
	abort ();		/* XXX */
    }
    if (mask & KADM5_FAIL_AUTH_COUNT) {
	abort ();		/* XXX */
    }
    if (mask & KADM5_KEY_DATA) {
	size_t num;
	size_t i;

	for (i = 0; i < ent.entry.keys.len; ++i)
	    free_Key(&ent.entry.keys.val[i]);
	free (ent.entry.keys.val);

	num = log_ent.entry.keys.len;

	ent.entry.keys.len = num;
	ent.entry.keys.val = malloc(len * sizeof(*ent.entry.keys.val));
	if (ent.entry.keys.val == NULL) {
	    krb5_set_error_message(context->context, ENOMEM, "out of memory");
	    return ENOMEM;
	}
	for (i = 0; i < ent.entry.keys.len; ++i) {
	    ret = copy_Key(&log_ent.entry.keys.val[i],
			   &ent.entry.keys.val[i]);
	    if (ret) {
		krb5_set_error_message(context->context, ret, "out of memory");
		goto out;
	    }
	}
    }
    if ((mask & KADM5_TL_DATA) && log_ent.entry.extensions) {
	HDB_extensions *es = ent.entry.extensions;

	ent.entry.extensions = calloc(1, sizeof(*ent.entry.extensions));
	if (ent.entry.extensions == NULL)
	    goto out;

	ret = copy_HDB_extensions(log_ent.entry.extensions,
				  ent.entry.extensions);
	if (ret) {
	    krb5_set_error_message(context->context, ret, "out of memory");
	    free(ent.entry.extensions);
	    ent.entry.extensions = es;
	    goto out;
	}
	if (es) {
	    free_HDB_extensions(es);
	    free(es);
	}
    }
    ret = context->db->hdb_store(context->context, context->db,
				 HDB_F_REPLACE, &ent);
 out:
    hdb_free_entry (context->context, &ent);
    hdb_free_entry (context->context, &log_ent);
    return ret;
}