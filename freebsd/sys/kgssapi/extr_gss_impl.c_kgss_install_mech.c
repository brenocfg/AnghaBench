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
struct kobj_class {int dummy; } ;
struct kgss_mech {char const* km_mech_name; struct kobj_class* km_class; int /*<<< orphan*/  km_mech_type; } ;
typedef  int /*<<< orphan*/  gss_OID ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct kgss_mech*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  kgss_mechs ; 
 int /*<<< orphan*/  km_link ; 
 struct kgss_mech* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kgss_install_mech(gss_OID mech_type, const char *name, struct kobj_class *cls)
{
	struct kgss_mech *km;

	km = malloc(sizeof(struct kgss_mech), M_GSSAPI, M_WAITOK);
	km->km_mech_type = mech_type;
	km->km_mech_name = name;
	km->km_class = cls;
	LIST_INSERT_HEAD(&kgss_mechs, km, km_link);
}