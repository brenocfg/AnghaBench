#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  iPAddress; int /*<<< orphan*/  uniformResourceIdentifier; int /*<<< orphan*/  rfc822Name; int /*<<< orphan*/  dNSName; int /*<<< orphan*/  directoryName; } ;
struct TYPE_6__ {int type; TYPE_1__ d; } ;
typedef  TYPE_2__ GENERAL_NAME ;

/* Variables and functions */
#define  GEN_DIRNAME 132 
#define  GEN_DNS 131 
#define  GEN_EMAIL 130 
#define  GEN_IPADD 129 
#define  GEN_URI 128 
 int X509_V_ERR_UNSUPPORTED_CONSTRAINT_TYPE ; 
 int nc_dn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nc_dns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nc_email (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nc_ip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nc_uri (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nc_match_single(GENERAL_NAME *gen, GENERAL_NAME *base)
{
    switch (base->type) {
    case GEN_DIRNAME:
        return nc_dn(gen->d.directoryName, base->d.directoryName);

    case GEN_DNS:
        return nc_dns(gen->d.dNSName, base->d.dNSName);

    case GEN_EMAIL:
        return nc_email(gen->d.rfc822Name, base->d.rfc822Name);

    case GEN_URI:
        return nc_uri(gen->d.uniformResourceIdentifier,
                      base->d.uniformResourceIdentifier);

    case GEN_IPADD:
        return nc_ip(gen->d.iPAddress, base->d.iPAddress);

    default:
        return X509_V_ERR_UNSUPPORTED_CONSTRAINT_TYPE;
    }

}