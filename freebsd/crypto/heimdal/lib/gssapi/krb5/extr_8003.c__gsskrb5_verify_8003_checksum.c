#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zeros ;
struct TYPE_7__ {unsigned char length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  hash ;
typedef  scalar_t__ gss_channel_bindings_t ;
struct TYPE_6__ {int length; unsigned char* data; } ;
struct TYPE_8__ {scalar_t__ cksumtype; TYPE_1__ checksum; } ;
typedef  int OM_uint32 ;
typedef  TYPE_3__ Checksum ;

/* Variables and functions */
 scalar_t__ CKSUMTYPE_GSSAPI ; 
 int ENOMEM ; 
 int GSS_C_DELEG_FLAG ; 
 scalar_t__ const GSS_C_NO_CHANNEL_BINDINGS ; 
 int GSS_S_BAD_BINDINGS ; 
 int GSS_S_COMPLETE ; 
 int GSS_S_FAILURE ; 
 int /*<<< orphan*/  _gsskrb5_decode_om_uint32 (unsigned char*,int*) ; 
 scalar_t__ ct_memcmp (unsigned char*,unsigned char*,int) ; 
 scalar_t__ hash_input_chan_bindings (scalar_t__ const,unsigned char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 

OM_uint32
_gsskrb5_verify_8003_checksum(
		      OM_uint32 *minor_status,
		      const gss_channel_bindings_t input_chan_bindings,
		      const Checksum *cksum,
		      OM_uint32 *flags,
		      krb5_data *fwd_data)
{
    unsigned char hash[16];
    unsigned char *p;
    OM_uint32 length;
    int DlgOpt;
    static unsigned char zeros[16];

    /* XXX should handle checksums > 24 bytes */
    if(cksum->cksumtype != CKSUMTYPE_GSSAPI || cksum->checksum.length < 24) {
	*minor_status = 0;
	return GSS_S_BAD_BINDINGS;
    }

    p = cksum->checksum.data;
    _gsskrb5_decode_om_uint32(p, &length);
    if(length != sizeof(hash)) {
	*minor_status = 0;
	return GSS_S_BAD_BINDINGS;
    }

    p += 4;

    if (input_chan_bindings != GSS_C_NO_CHANNEL_BINDINGS
	&& memcmp(p, zeros, sizeof(zeros)) != 0) {
	if(hash_input_chan_bindings(input_chan_bindings, hash) != 0) {
	    *minor_status = 0;
	    return GSS_S_BAD_BINDINGS;
	}
	if(ct_memcmp(hash, p, sizeof(hash)) != 0) {
	    *minor_status = 0;
	    return GSS_S_BAD_BINDINGS;
	}
    }

    p += sizeof(hash);

    _gsskrb5_decode_om_uint32(p, flags);
    p += 4;

    if (cksum->checksum.length > 24 && (*flags & GSS_C_DELEG_FLAG)) {
	if(cksum->checksum.length < 28) {
	    *minor_status = 0;
	    return GSS_S_BAD_BINDINGS;
	}

	DlgOpt = (p[0] << 0) | (p[1] << 8);
	p += 2;
	if (DlgOpt != 1) {
	    *minor_status = 0;
	    return GSS_S_BAD_BINDINGS;
	}

	fwd_data->length = (p[0] << 0) | (p[1] << 8);
	p += 2;
	if(cksum->checksum.length < 28 + fwd_data->length) {
	    *minor_status = 0;
	    return GSS_S_BAD_BINDINGS;
	}
	fwd_data->data = malloc(fwd_data->length);
	if (fwd_data->data == NULL) {
	    *minor_status = ENOMEM;
	    return GSS_S_FAILURE;
	}
	memcpy(fwd_data->data, p, fwd_data->length);
    }

    return GSS_S_COMPLETE;
}