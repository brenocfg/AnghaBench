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
struct timeval {int dummy; } ;
struct krb5_key_state {struct des3_state* ks_priv; } ;
struct des3_state {int /*<<< orphan*/  ds_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_GSSAPI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  gone_in (int,char*) ; 
 int /*<<< orphan*/  krb5_warn_interval ; 
 struct des3_state* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ratecheck (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
des3_init(struct krb5_key_state *ks)
{
	static struct timeval lastwarn;
	struct des3_state *ds;

	ds = malloc(sizeof(struct des3_state), M_GSSAPI, M_WAITOK|M_ZERO);
	mtx_init(&ds->ds_lock, "gss des3 lock", NULL, MTX_DEF);
	ks->ks_priv = ds;
	if (ratecheck(&lastwarn, &krb5_warn_interval))
		gone_in(13, "DES3 cipher for Kerberos GSS");
}