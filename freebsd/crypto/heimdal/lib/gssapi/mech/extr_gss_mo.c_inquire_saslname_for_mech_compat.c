#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gss_mech_compat_desc_struct {int /*<<< orphan*/  (* gmc_inquire_saslname_for_mech ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* gssapi_mech_interface ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
typedef  int /*<<< orphan*/  gss_OID ;
struct TYPE_3__ {struct gss_mech_compat_desc_struct* gm_compat; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_S_BAD_MECH ; 
 int /*<<< orphan*/  GSS_S_UNAVAILABLE ; 
 TYPE_1__* __gss_get_mechanism (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OM_uint32
inquire_saslname_for_mech_compat(OM_uint32 *minor,
                                 const gss_OID desired_mech,
                                 gss_buffer_t sasl_mech_name,
                                 gss_buffer_t mech_name,
                                 gss_buffer_t mech_description)
{
    struct gss_mech_compat_desc_struct *gmc;
    gssapi_mech_interface m;
    OM_uint32 major;

    m = __gss_get_mechanism(desired_mech);
    if (m == NULL)
        return GSS_S_BAD_MECH;

    gmc = m->gm_compat;

    if (gmc != NULL && gmc->gmc_inquire_saslname_for_mech != NULL) {
        major = gmc->gmc_inquire_saslname_for_mech(minor,
                                                   desired_mech,
                                                   sasl_mech_name,
                                                   mech_name,
                                                   mech_description);
    } else {
        major = GSS_S_UNAVAILABLE;
    }

    return major;
}