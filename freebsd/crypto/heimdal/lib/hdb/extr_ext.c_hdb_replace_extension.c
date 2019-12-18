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
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_20__ {TYPE_15__* extensions; } ;
typedef  TYPE_4__ hdb_entry ;
struct TYPE_17__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_18__ {TYPE_1__ asn1_ellipsis; } ;
struct TYPE_19__ {scalar_t__ element; TYPE_2__ u; } ;
struct TYPE_21__ {TYPE_3__ data; } ;
struct TYPE_16__ {size_t len; TYPE_5__* val; } ;
typedef  TYPE_5__ HDB_extension ;
typedef  int /*<<< orphan*/  Der_type ;
typedef  int /*<<< orphan*/  Der_class ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ MAKE_TAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_15__* calloc (int,int) ; 
 scalar_t__ choice_HDB_extension_data_asn1_ellipsis ; 
 int copy_HDB_extension (TYPE_5__ const*,TYPE_5__*) ; 
 int der_get_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,size_t*) ; 
 int /*<<< orphan*/  free_HDB_extension (TYPE_5__*) ; 
 TYPE_5__* hdb_find_extension (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_5__* realloc (TYPE_5__*,int) ; 

krb5_error_code
hdb_replace_extension(krb5_context context,
		      hdb_entry *entry,
		      const HDB_extension *ext)
{
    HDB_extension *ext2;
    HDB_extension *es;
    int ret;

    ext2 = NULL;

    if (entry->extensions == NULL) {
	entry->extensions = calloc(1, sizeof(*entry->extensions));
	if (entry->extensions == NULL) {
	    krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	    return ENOMEM;
	}
    } else if (ext->data.element != choice_HDB_extension_data_asn1_ellipsis) {
	ext2 = hdb_find_extension(entry, ext->data.element);
    } else {
	/*
	 * This is an unknown extention, and we are asked to replace a
	 * possible entry in `entry' that is of the same type. This
	 * might seem impossible, but ASN.1 CHOICE comes to our
	 * rescue. The first tag in each branch in the CHOICE is
	 * unique, so just find the element in the list that have the
	 * same tag was we are putting into the list.
	 */
	Der_class replace_class, list_class;
	Der_type replace_type, list_type;
	unsigned int replace_tag, list_tag;
	size_t size;
	size_t i;

	ret = der_get_tag(ext->data.u.asn1_ellipsis.data,
			  ext->data.u.asn1_ellipsis.length,
			  &replace_class, &replace_type, &replace_tag,
			  &size);
	if (ret) {
	    krb5_set_error_message(context, ret, "hdb: failed to decode "
				   "replacement hdb extention");
	    return ret;
	}

	for (i = 0; i < entry->extensions->len; i++) {
	    HDB_extension *ext3 = &entry->extensions->val[i];

	    if (ext3->data.element != choice_HDB_extension_data_asn1_ellipsis)
		continue;

	    ret = der_get_tag(ext3->data.u.asn1_ellipsis.data,
			      ext3->data.u.asn1_ellipsis.length,
			      &list_class, &list_type, &list_tag,
			      &size);
	    if (ret) {
		krb5_set_error_message(context, ret, "hdb: failed to decode "
				       "present hdb extention");
		return ret;
	    }

	    if (MAKE_TAG(replace_class,replace_type,replace_type) ==
		MAKE_TAG(list_class,list_type,list_type)) {
		ext2 = ext3;
		break;
	    }
	}
    }

    if (ext2) {
	free_HDB_extension(ext2);
	ret = copy_HDB_extension(ext, ext2);
	if (ret)
	    krb5_set_error_message(context, ret, "hdb: failed to copy replacement "
				   "hdb extention");
	return ret;
    }

    es = realloc(entry->extensions->val,
		 (entry->extensions->len+1)*sizeof(entry->extensions->val[0]));
    if (es == NULL) {
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }
    entry->extensions->val = es;

    ret = copy_HDB_extension(ext,
			     &entry->extensions->val[entry->extensions->len]);
    if (ret == 0)
	entry->extensions->len++;
    else
	krb5_set_error_message(context, ret, "hdb: failed to copy new extension");

    return ret;
}