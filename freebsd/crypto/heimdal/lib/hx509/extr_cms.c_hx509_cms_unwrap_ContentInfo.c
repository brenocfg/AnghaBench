#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_oid ;
typedef  TYPE_1__ heim_octet_string ;
struct TYPE_14__ {int /*<<< orphan*/ * content; int /*<<< orphan*/  contentType; } ;
typedef  TYPE_3__ ContentInfo ;

/* Variables and functions */
 int decode_ContentInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,size_t*) ; 
 int der_copy_octet_string (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int der_copy_oid (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  der_free_oid (TYPE_1__*) ; 
 int /*<<< orphan*/  free_ContentInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int
hx509_cms_unwrap_ContentInfo(const heim_octet_string *in,
			     heim_oid *oid,
			     heim_octet_string *out,
			     int *have_data)
{
    ContentInfo ci;
    size_t size;
    int ret;

    memset(oid, 0, sizeof(*oid));
    memset(out, 0, sizeof(*out));

    ret = decode_ContentInfo(in->data, in->length, &ci, &size);
    if (ret)
	return ret;

    ret = der_copy_oid(&ci.contentType, oid);
    if (ret) {
	free_ContentInfo(&ci);
	return ret;
    }
    if (ci.content) {
	ret = der_copy_octet_string(ci.content, out);
	if (ret) {
	    der_free_oid(oid);
	    free_ContentInfo(&ci);
	    return ret;
	}
    } else
	memset(out, 0, sizeof(*out));

    if (have_data)
	*have_data = (ci.content != NULL) ? 1 : 0;

    free_ContentInfo(&ci);

    return 0;
}