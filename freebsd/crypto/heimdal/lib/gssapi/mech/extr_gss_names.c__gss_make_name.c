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
struct _gss_name {int /*<<< orphan*/  gn_mn; } ;
struct _gss_mechanism_name {int /*<<< orphan*/  gmn_name; int /*<<< orphan*/ * gmn_mech_oid; TYPE_1__* gmn_mech; } ;
typedef  TYPE_1__* gssapi_mech_interface ;
typedef  int /*<<< orphan*/  gss_name_t ;
struct TYPE_3__ {int /*<<< orphan*/  gm_mech_oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIM_SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIM_SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct _gss_mechanism_name*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct _gss_name*) ; 
 int /*<<< orphan*/  gmn_link ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (struct _gss_name*,int /*<<< orphan*/ ,int) ; 

struct _gss_name *
_gss_make_name(gssapi_mech_interface m, gss_name_t new_mn)
{
	struct _gss_name *name;
	struct _gss_mechanism_name *mn;

	name = malloc(sizeof(struct _gss_name));
	if (!name)
		return (0);
	memset(name, 0, sizeof(struct _gss_name));

	mn = malloc(sizeof(struct _gss_mechanism_name));
	if (!mn) {
		free(name);
		return (0);
	}

	HEIM_SLIST_INIT(&name->gn_mn);
	mn->gmn_mech = m;
	mn->gmn_mech_oid = &m->gm_mech_oid;
	mn->gmn_name = new_mn;
	HEIM_SLIST_INSERT_HEAD(&name->gn_mn, mn, gmn_link);

	return (name);
}