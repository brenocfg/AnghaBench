#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cert_status {int haveIAN; } ;
typedef  int /*<<< orphan*/  hx509_validate_ctx ;
typedef  enum critical_flag { ____Placeholder_critical_flag } critical_flag ;
typedef  int /*<<< orphan*/  Extension ;

/* Variables and functions */
 int check_altName (int /*<<< orphan*/ ,struct cert_status*,char*,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
check_issuerAltName(hx509_validate_ctx ctx,
		    struct cert_status *status,
		     enum critical_flag cf,
		     const Extension *e)
{
    status->haveIAN = 1;
    return check_altName(ctx, status, "issuer", cf, e);
}