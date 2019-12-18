#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mechbuf ;
typedef  int /*<<< orphan*/  hostname ;
typedef  int /*<<< orphan*/  gss_name_t ;
struct TYPE_17__ {char* value; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  TYPE_2__* gss_OID_set ;
struct TYPE_19__ {size_t length; char* elements; } ;
typedef  TYPE_3__ gss_OID_desc ;
typedef  TYPE_3__* gss_OID ;
struct TYPE_18__ {size_t count; TYPE_3__* elements; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  MechType ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  GSS_C_NO_NAME ; 
 int /*<<< orphan*/  GSS_C_NT_HOSTBASED_SERVICE ; 
 TYPE_3__* GSS_SPNEGO_MECHANISM ; 
 scalar_t__ GSS_S_BAD_MECH ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_DEFECTIVE_TOKEN ; 
 scalar_t__ GSS_S_FAILURE ; 
 int MAXHOSTNAMELEN ; 
 TYPE_3__ _gss_spnego_krb5_mechanism_oid_desc ; 
 TYPE_3__ _gss_spnego_mskrb_mechanism_oid_desc ; 
 scalar_t__ acceptor_approved (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int asprintf (char**,char*,char*) ; 
 scalar_t__ der_put_oid (unsigned char*,int,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ gethostname (char*,int) ; 
 scalar_t__ gss_duplicate_oid (scalar_t__*,TYPE_3__*,TYPE_3__**) ; 
 scalar_t__ gss_import_name (scalar_t__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_indicate_mechs (scalar_t__*,TYPE_2__**) ; 
 scalar_t__ gss_oid_equal (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  gss_release_name (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_oid_set (scalar_t__*,TYPE_2__**) ; 
 scalar_t__ issuid () ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static OM_uint32
select_mech(OM_uint32 *minor_status, MechType *mechType, int verify_p,
	    gss_OID *mech_p)
{
    char mechbuf[64];
    size_t mech_len;
    gss_OID_desc oid;
    gss_OID oidp;
    gss_OID_set mechs;
    size_t i;
    OM_uint32 ret, junk;

    ret = der_put_oid ((unsigned char *)mechbuf + sizeof(mechbuf) - 1,
		       sizeof(mechbuf),
		       mechType,
		       &mech_len);
    if (ret) {
	return GSS_S_DEFECTIVE_TOKEN;
    }

    oid.length   = mech_len;
    oid.elements = mechbuf + sizeof(mechbuf) - mech_len;

    if (gss_oid_equal(&oid, GSS_SPNEGO_MECHANISM)) {
	return GSS_S_BAD_MECH;
    }

    *minor_status = 0;

    /* Translate broken MS Kebreros OID */
    if (gss_oid_equal(&oid, &_gss_spnego_mskrb_mechanism_oid_desc))
	    oidp = &_gss_spnego_krb5_mechanism_oid_desc;
    else
	    oidp = &oid;


    ret = gss_indicate_mechs(&junk, &mechs);
    if (ret)
	    return (ret);

    for (i = 0; i < mechs->count; i++)
	    if (gss_oid_equal(&mechs->elements[i], oidp))
		    break;

    if (i == mechs->count) {
	    gss_release_oid_set(&junk, &mechs);
	    return GSS_S_BAD_MECH;
    }
    gss_release_oid_set(&junk, &mechs);

    ret = gss_duplicate_oid(minor_status,
			    &oid, /* possibly this should be oidp */
			    mech_p);

    if (verify_p) {
	gss_name_t name = GSS_C_NO_NAME;
	gss_buffer_desc namebuf;
	char *str = NULL, *host, hostname[MAXHOSTNAMELEN];

	host = getenv("GSSAPI_SPNEGO_NAME");
	if (host == NULL || issuid()) {
	    int rv;
	    if (gethostname(hostname, sizeof(hostname)) != 0) {
		*minor_status = errno;
		return GSS_S_FAILURE;
	    }
	    rv = asprintf(&str, "host@%s", hostname);
	    if (rv < 0 || str == NULL) {
		*minor_status = ENOMEM;
		return GSS_S_FAILURE;
	    }
	    host = str;
	}

	namebuf.length = strlen(host);
	namebuf.value = host;

	ret = gss_import_name(minor_status, &namebuf,
			      GSS_C_NT_HOSTBASED_SERVICE, &name);
	if (str)
	    free(str);
	if (ret != GSS_S_COMPLETE)
	    return ret;

	ret = acceptor_approved(name, *mech_p);
	gss_release_name(&junk, &name);
    }

    return ret;
}