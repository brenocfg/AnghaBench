#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int u_char ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_14__ {int len; TYPE_4__* val; } ;
struct TYPE_16__ {int kvno; TYPE_1__ keys; } ;
typedef  TYPE_3__ hdb_entry ;
struct TYPE_18__ {scalar_t__ data; } ;
struct TYPE_15__ {int keytype; TYPE_9__ keyvalue; } ;
struct TYPE_17__ {int* mkvno; TYPE_12__* salt; TYPE_2__ key; } ;
struct TYPE_13__ {unsigned int type; TYPE_9__ salt; } ;
typedef  TYPE_4__ Key ;

/* Variables and functions */
 TYPE_12__* calloc (int,int) ; 
 int /*<<< orphan*/  context ; 
 scalar_t__ krb5_data_alloc (TYPE_9__*,size_t) ; 
 scalar_t__ krb5_data_copy (TYPE_9__*,char*,size_t) ; 
 int /*<<< orphan*/  krb5_data_zero (TYPE_9__*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* realloc (TYPE_4__*,int) ; 
 int sscanf (char*,char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
parse_keys(hdb_entry *ent, char *str)
{
    krb5_error_code ret;
    int tmp;
    char *p;
    size_t i;

    p = strsep(&str, ":");
    if (sscanf(p, "%d", &tmp) != 1)
	return 1;
    ent->kvno = tmp;
    p = strsep(&str, ":");
    while(p){
	Key *key;
	key = realloc(ent->keys.val,
		      (ent->keys.len + 1) * sizeof(*ent->keys.val));
	if(key == NULL)
	    krb5_errx (context, 1, "realloc: out of memory");
	ent->keys.val = key;
	key = ent->keys.val + ent->keys.len;
	ent->keys.len++;
	memset(key, 0, sizeof(*key));
	if(sscanf(p, "%d", &tmp) == 1) {
	    key->mkvno = malloc(sizeof(*key->mkvno));
	    *key->mkvno = tmp;
	} else
	    key->mkvno = NULL;
	p = strsep(&str, ":");
	if (sscanf(p, "%d", &tmp) != 1)
	    return 1;
	key->key.keytype = tmp;
	p = strsep(&str, ":");
	ret = krb5_data_alloc(&key->key.keyvalue, (strlen(p) - 1) / 2 + 1);
	if (ret)
	    krb5_err (context, 1, ret, "krb5_data_alloc");
	for(i = 0; i < strlen(p); i += 2) {
	    if(sscanf(p + i, "%02x", &tmp) != 1)
		return 1;
	    ((u_char*)key->key.keyvalue.data)[i / 2] = tmp;
	}
	p = strsep(&str, ":");
	if(strcmp(p, "-") != 0){
	    unsigned type;
	    size_t p_len;

	    if(sscanf(p, "%u/", &type) != 1)
		return 1;
	    p = strchr(p, '/');
	    if(p == NULL)
		return 1;
	    p++;
	    p_len = strlen(p);

	    key->salt = calloc(1, sizeof(*key->salt));
	    if (key->salt == NULL)
		krb5_errx (context, 1, "malloc: out of memory");
	    key->salt->type = type;

	    if (p_len) {
		if(*p == '\"') {
		    ret = krb5_data_copy(&key->salt->salt, p + 1, p_len - 2);
		    if (ret)
			krb5_err (context, 1, ret, "krb5_data_copy");
		} else {
		    ret = krb5_data_alloc(&key->salt->salt,
					  (p_len - 1) / 2 + 1);
		    if (ret)
			krb5_err (context, 1, ret, "krb5_data_alloc");
		    for(i = 0; i < p_len; i += 2){
			if (sscanf(p + i, "%02x", &tmp) != 1)
			    return 1;
			((u_char*)key->salt->salt.data)[i / 2] = tmp;
		    }
		}
	    } else
		krb5_data_zero (&key->salt->salt);
	}
	p = strsep(&str, ":");
    }
    return 0;
}