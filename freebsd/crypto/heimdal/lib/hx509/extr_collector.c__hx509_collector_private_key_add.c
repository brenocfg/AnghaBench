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
struct private_key {int /*<<< orphan*/  localKeyId; scalar_t__ private_key; int /*<<< orphan*/  alg; } ;
struct TYPE_6__ {int len; struct private_key** data; } ;
struct hx509_collector {TYPE_1__ val; } ;
typedef  scalar_t__ hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_7__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ heim_octet_string ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HX509_KEY_FORMAT_DER ; 
 struct private_key* calloc (int,int) ; 
 int copy_AlgorithmIdentifier (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int der_copy_octet_string (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct private_key*) ; 
 int /*<<< orphan*/  free_private_key (struct private_key*) ; 
 int hx509_parse_private_key (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* realloc (struct private_key**,int) ; 

int
_hx509_collector_private_key_add(hx509_context context,
				 struct hx509_collector *c,
				 const AlgorithmIdentifier *alg,
				 hx509_private_key private_key,
				 const heim_octet_string *key_data,
				 const heim_octet_string *localKeyId)
{
    struct private_key *key;
    void *d;
    int ret;

    key = calloc(1, sizeof(*key));
    if (key == NULL)
	return ENOMEM;

    d = realloc(c->val.data, (c->val.len + 1) * sizeof(c->val.data[0]));
    if (d == NULL) {
	free(key);
	hx509_set_error_string(context, 0, ENOMEM, "Out of memory");
	return ENOMEM;
    }
    c->val.data = d;

    ret = copy_AlgorithmIdentifier(alg, &key->alg);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "Failed to copy "
			       "AlgorithmIdentifier");
	goto out;
    }
    if (private_key) {
	key->private_key = private_key;
    } else {
	ret = hx509_parse_private_key(context, alg,
				       key_data->data, key_data->length,
				       HX509_KEY_FORMAT_DER,
				       &key->private_key);
	if (ret)
	    goto out;
    }
    if (localKeyId) {
	ret = der_copy_octet_string(localKeyId, &key->localKeyId);
	if (ret) {
	    hx509_set_error_string(context, 0, ret,
				   "Failed to copy localKeyId");
	    goto out;
	}
    } else
	memset(&key->localKeyId, 0, sizeof(key->localKeyId));

    c->val.data[c->val.len] = key;
    c->val.len++;

out:
    if (ret)
	free_private_key(key);

    return ret;
}