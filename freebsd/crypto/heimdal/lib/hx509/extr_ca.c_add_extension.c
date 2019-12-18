#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_oid ;
typedef  int /*<<< orphan*/  heim_octet_string ;
typedef  int /*<<< orphan*/  ext ;
struct TYPE_8__ {int /*<<< orphan*/  extnValue; int /*<<< orphan*/  extnID; int /*<<< orphan*/ * critical; } ;
struct TYPE_7__ {int /*<<< orphan*/  extensions; } ;
typedef  TYPE_1__ TBSCertificate ;
typedef  TYPE_2__ Extension ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  TRUE ; 
 int add_Extensions (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int der_copy_octet_string (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int der_copy_oid (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_Extension (TYPE_2__*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
add_extension(hx509_context context,
	      TBSCertificate *tbsc,
	      int critical_flag,
	      const heim_oid *oid,
	      const heim_octet_string *data)
{
    Extension ext;
    int ret;

    memset(&ext, 0, sizeof(ext));

    if (critical_flag) {
	ext.critical = malloc(sizeof(*ext.critical));
	if (ext.critical == NULL) {
	    ret = ENOMEM;
	    hx509_set_error_string(context, 0, ret, "Out of memory");
	    goto out;
	}
	*ext.critical = TRUE;
    }

    ret = der_copy_oid(oid, &ext.extnID);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "Out of memory");
	goto out;
    }
    ret = der_copy_octet_string(data, &ext.extnValue);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "Out of memory");
	goto out;
    }
    ret = add_Extensions(tbsc->extensions, &ext);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "Out of memory");
	goto out;
    }
out:
    free_Extension(&ext);
    return ret;
}