#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_12__ {size_t len; TYPE_3__* val; } ;
struct TYPE_15__ {TYPE_6__* extensions; TYPE_5__* generation; int /*<<< orphan*/  flags; int /*<<< orphan*/ * max_renew; int /*<<< orphan*/ * max_life; int /*<<< orphan*/ * pw_end; int /*<<< orphan*/ * valid_end; int /*<<< orphan*/ * valid_start; int /*<<< orphan*/ * modified_by; int /*<<< orphan*/  created_by; TYPE_4__ keys; int /*<<< orphan*/  kvno; int /*<<< orphan*/  principal; } ;
typedef  TYPE_7__ hdb_entry ;
struct TYPE_14__ {size_t len; int /*<<< orphan*/ * val; } ;
struct TYPE_13__ {int /*<<< orphan*/  gen; int /*<<< orphan*/  usec; int /*<<< orphan*/  time; } ;
struct TYPE_9__ {int /*<<< orphan*/  keyvalue; int /*<<< orphan*/  keytype; } ;
struct TYPE_11__ {TYPE_2__* salt; TYPE_1__ key; int /*<<< orphan*/ * mkvno; } ;
struct TYPE_10__ {int /*<<< orphan*/  salt; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_MALLOC_ENCODE (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *,size_t*,scalar_t__) ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  HDBFlags2int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDB_extension ; 
 int /*<<< orphan*/  append_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hex_encode (void*,size_t,char**) ; 
 int /*<<< orphan*/  krb5_abortx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  time2str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
entry2string_int (krb5_context context, krb5_storage *sp, hdb_entry *ent)
{
    char *p;
    size_t i;
    krb5_error_code ret;

    /* --- principal */
    ret = krb5_unparse_name(context, ent->principal, &p);
    if(ret)
	return ret;
    append_string(context, sp, "%s ", p);
    free(p);
    /* --- kvno */
    append_string(context, sp, "%d", ent->kvno);
    /* --- keys */
    for(i = 0; i < ent->keys.len; i++){
	/* --- mkvno, keytype */
	if(ent->keys.val[i].mkvno)
	    append_string(context, sp, ":%d:%d:",
			  *ent->keys.val[i].mkvno,
			  ent->keys.val[i].key.keytype);
	else
	    append_string(context, sp, "::%d:",
			  ent->keys.val[i].key.keytype);
	/* --- keydata */
	append_hex(context, sp, &ent->keys.val[i].key.keyvalue);
	append_string(context, sp, ":");
	/* --- salt */
	if(ent->keys.val[i].salt){
	    append_string(context, sp, "%u/", ent->keys.val[i].salt->type);
	    append_hex(context, sp, &ent->keys.val[i].salt->salt);
	}else
	    append_string(context, sp, "-");
    }
    append_string(context, sp, " ");
    /* --- created by */
    append_event(context, sp, &ent->created_by);
    /* --- modified by */
    append_event(context, sp, ent->modified_by);

    /* --- valid start */
    if(ent->valid_start)
	append_string(context, sp, "%s ", time2str(*ent->valid_start));
    else
	append_string(context, sp, "- ");

    /* --- valid end */
    if(ent->valid_end)
	append_string(context, sp, "%s ", time2str(*ent->valid_end));
    else
	append_string(context, sp, "- ");

    /* --- password ends */
    if(ent->pw_end)
	append_string(context, sp, "%s ", time2str(*ent->pw_end));
    else
	append_string(context, sp, "- ");

    /* --- max life */
    if(ent->max_life)
	append_string(context, sp, "%d ", *ent->max_life);
    else
	append_string(context, sp, "- ");

    /* --- max renewable life */
    if(ent->max_renew)
	append_string(context, sp, "%d ", *ent->max_renew);
    else
	append_string(context, sp, "- ");

    /* --- flags */
    append_string(context, sp, "%d ", HDBFlags2int(ent->flags));

    /* --- generation number */
    if(ent->generation) {
	append_string(context, sp, "%s:%d:%d ", time2str(ent->generation->time),
		      ent->generation->usec,
		      ent->generation->gen);
    } else
	append_string(context, sp, "- ");

    /* --- extensions */
    if(ent->extensions && ent->extensions->len > 0) {
	for(i = 0; i < ent->extensions->len; i++) {
	    void *d;
	    size_t size, sz = 0;

	    ASN1_MALLOC_ENCODE(HDB_extension, d, size,
			       &ent->extensions->val[i], &sz, ret);
	    if (ret) {
		krb5_clear_error_message(context);
		return ret;
	    }
	    if(size != sz)
		krb5_abortx(context, "internal asn.1 encoder error");

	    if (hex_encode(d, size, &p) < 0) {
		free(d);
		krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
		return ENOMEM;
	    }

	    free(d);
	    append_string(context, sp, "%s%s", p,
			  ent->extensions->len - 1 != i ? ":" : "");
	    free(p);
	}
    } else
	append_string(context, sp, "-");


    return 0;
}