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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int km_jitter_window; void* km_flags; void** km_elem; void* km_first_seq; void* km_length; void* km_start; } ;
struct krb5_context {int /*<<< orphan*/  kc_remote_subkey; int /*<<< orphan*/  kc_local_subkey; int /*<<< orphan*/  kc_keyblock; TYPE_1__ kc_msg_order; void* kc_lifetime; void* kc_more_flags; void* kc_ctx_flags; int /*<<< orphan*/  kc_target_name; int /*<<< orphan*/  kc_source_name; void* kc_cksumtype; void* kc_keytype; void* kc_remote_seqnumber; void* kc_local_seqnumber; void* kc_remote_port; void* kc_local_port; int /*<<< orphan*/  kc_remote_address; int /*<<< orphan*/  kc_local_address; void* kc_ac_flags; } ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  TYPE_2__* gss_buffer_t ;
typedef  enum sec_context_format { ____Placeholder_sec_context_format } sec_context_format ;
struct TYPE_7__ {int const length; int /*<<< orphan*/  elements; } ;
struct TYPE_6__ {size_t length; scalar_t__ value; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_DEFECTIVE_TOKEN ; 
 int KGSS_HEIMDAL_0_6 ; 
 int KGSS_HEIMDAL_1_1 ; 
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int SC_KEYBLOCK ; 
 int SC_LOCAL_ADDRESS ; 
 int SC_LOCAL_SUBKEY ; 
 int SC_REMOTE_ADDRESS ; 
 int SC_REMOTE_SUBKEY ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  delete_keyblock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_address (int const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_data (int const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_keyblock (int const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_keys (struct krb5_context*) ; 
 void* get_uint16 (int const**,size_t*) ; 
 void* get_uint32 (int const**,size_t*) ; 
 TYPE_3__ krb5_mech_oid ; 
 void** malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OM_uint32
krb5_import(gss_ctx_id_t ctx,
    enum sec_context_format format,
    const gss_buffer_t context_token)
{
	struct krb5_context *kc = (struct krb5_context *)ctx;
	OM_uint32 res;
	const uint8_t *p = (const uint8_t *) context_token->value;
	size_t len = context_token->length;
	uint32_t flags;
	int i;
	
	/*
	 * We support heimdal 0.6 and heimdal 1.1
	 */
	if (format != KGSS_HEIMDAL_0_6 && format != KGSS_HEIMDAL_1_1)
		return (GSS_S_DEFECTIVE_TOKEN);

#define SC_LOCAL_ADDRESS	1
#define SC_REMOTE_ADDRESS	2
#define SC_KEYBLOCK		4
#define SC_LOCAL_SUBKEY		8
#define SC_REMOTE_SUBKEY	16

	/*
	 * Ensure that the token starts with krb5 oid.
	 */
	if (p[0] != 0x00 || p[1] != krb5_mech_oid.length
	    || len < krb5_mech_oid.length + 2
	    || bcmp(krb5_mech_oid.elements, p + 2,
		krb5_mech_oid.length))
		return (GSS_S_DEFECTIVE_TOKEN);
	p += krb5_mech_oid.length + 2;
	len -= krb5_mech_oid.length + 2;

	flags = get_uint32(&p, &len);
	kc->kc_ac_flags = get_uint32(&p, &len);
	if (flags & SC_LOCAL_ADDRESS)
		get_address(&p, &len, &kc->kc_local_address);
	if (flags & SC_REMOTE_ADDRESS)
		get_address(&p, &len, &kc->kc_remote_address);
	kc->kc_local_port = get_uint16(&p, &len);
	kc->kc_remote_port = get_uint16(&p, &len);
	if (flags & SC_KEYBLOCK)
		get_keyblock(&p, &len, &kc->kc_keyblock);
	if (flags & SC_LOCAL_SUBKEY)
		get_keyblock(&p, &len, &kc->kc_local_subkey);
	if (flags & SC_REMOTE_SUBKEY)
		get_keyblock(&p, &len, &kc->kc_remote_subkey);
	kc->kc_local_seqnumber = get_uint32(&p, &len);
	kc->kc_remote_seqnumber = get_uint32(&p, &len);
	kc->kc_keytype = get_uint32(&p, &len);
	kc->kc_cksumtype = get_uint32(&p, &len);
	get_data(&p, &len, &kc->kc_source_name);
	get_data(&p, &len, &kc->kc_target_name);
	kc->kc_ctx_flags = get_uint32(&p, &len);
	kc->kc_more_flags = get_uint32(&p, &len);
	kc->kc_lifetime = get_uint32(&p, &len);
	/*
	 * Heimdal 1.1 adds the message order stuff.
	 */
	if (format == KGSS_HEIMDAL_1_1) {
		kc->kc_msg_order.km_flags = get_uint32(&p, &len);
		kc->kc_msg_order.km_start = get_uint32(&p, &len);
		kc->kc_msg_order.km_length = get_uint32(&p, &len);
		kc->kc_msg_order.km_jitter_window = get_uint32(&p, &len);
		kc->kc_msg_order.km_first_seq = get_uint32(&p, &len);
		kc->kc_msg_order.km_elem =
			malloc(kc->kc_msg_order.km_jitter_window * sizeof(uint32_t),
			    M_GSSAPI, M_WAITOK);
		for (i = 0; i < kc->kc_msg_order.km_jitter_window; i++)
			kc->kc_msg_order.km_elem[i] = get_uint32(&p, &len);
	} else {
		kc->kc_msg_order.km_flags = 0;
	}

	res = get_keys(kc);
	if (GSS_ERROR(res))
		return (res);

	/*
	 * We don't need these anymore.
	 */
	delete_keyblock(&kc->kc_keyblock);
	delete_keyblock(&kc->kc_local_subkey);
	delete_keyblock(&kc->kc_remote_subkey);

	return (GSS_S_COMPLETE);
}