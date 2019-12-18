#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int krb5_preauthtype ;
struct TYPE_17__ {TYPE_4__* val; } ;
typedef  TYPE_5__ krb5_preauthdata ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_19__ {TYPE_1__* e_data; } ;
struct TYPE_18__ {size_t len; TYPE_3__* val; } ;
struct TYPE_16__ {int type; int /*<<< orphan*/  info; } ;
struct TYPE_14__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {int padata_type; TYPE_2__ padata_value; } ;
struct TYPE_13__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_6__ METHOD_DATA ;
typedef  TYPE_7__ KRB_ERROR ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_SEQ (TYPE_5__*,int) ; 
#define  KRB5_PADATA_ENC_TIMESTAMP 130 
#define  KRB5_PADATA_ETYPE_INFO 129 
#define  KRB5_PADATA_NONE 128 
 int /*<<< orphan*/  decode_ETYPE_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_METHOD_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_METHOD_DATA (TYPE_6__*) ; 

__attribute__((used)) static int
set_ptypes(krb5_context context,
	   KRB_ERROR *error,
	   const krb5_preauthtype **ptypes,
	   krb5_preauthdata **preauth)
{
    static krb5_preauthdata preauth2;
    static krb5_preauthtype ptypes2[] = { KRB5_PADATA_ENC_TIMESTAMP, KRB5_PADATA_NONE };

    if(error->e_data) {
	METHOD_DATA md;
	size_t i;
	decode_METHOD_DATA(error->e_data->data,
			   error->e_data->length,
			   &md,
			   NULL);
	for(i = 0; i < md.len; i++){
	    switch(md.val[i].padata_type){
	    case KRB5_PADATA_ENC_TIMESTAMP:
		*ptypes = ptypes2;
		break;
	    case KRB5_PADATA_ETYPE_INFO:
		*preauth = &preauth2;
		ALLOC_SEQ(*preauth, 1);
		(*preauth)->val[0].type = KRB5_PADATA_ENC_TIMESTAMP;
		decode_ETYPE_INFO(md.val[i].padata_value.data,
				  md.val[i].padata_value.length,
				  &(*preauth)->val[0].info,
				  NULL);
		break;
	    default:
		break;
	    }
	}
	free_METHOD_DATA(&md);
    } else {
	*ptypes = ptypes2;
    }
    return(1);
}