#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int len; TYPE_5__* val; } ;
struct TYPE_9__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_1__ byKey; int /*<<< orphan*/  byName; } ;
struct TYPE_11__ {int element; TYPE_2__ u; } ;
struct TYPE_15__ {TYPE_6__ responses; int /*<<< orphan*/  producedAt; TYPE_3__ responderID; } ;
struct TYPE_16__ {TYPE_7__ tbsResponseData; } ;
struct revoke_ocsp {scalar_t__ certs; TYPE_8__ ocsp; int /*<<< orphan*/ * path; } ;
typedef  int /*<<< orphan*/  ocsp ;
typedef  int /*<<< orphan*/  hx509_name ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_12__ {int element; } ;
struct TYPE_13__ {int /*<<< orphan*/  thisUpdate; scalar_t__ nextUpdate; TYPE_4__ certStatus; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  _hx509_abort (char*) ; 
 int /*<<< orphan*/  _hx509_name_from_Name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  choice_OCSPCertStatus_good 132 
#define  choice_OCSPCertStatus_revoked 131 
#define  choice_OCSPCertStatus_unknown 130 
#define  choice_OCSPResponderID_byKey 129 
#define  choice_OCSPResponderID_byName 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_ocsp (struct revoke_ocsp*) ; 
 int /*<<< orphan*/  hex_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int hx509_certs_iter_f (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_ci_print_names ; 
 int /*<<< orphan*/  hx509_name_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_name_to_string (int /*<<< orphan*/ ,char**) ; 
 int load_ocsp (int /*<<< orphan*/ ,struct revoke_ocsp*) ; 
 int /*<<< orphan*/  memset (struct revoke_ocsp*,int /*<<< orphan*/ ,int) ; 
 char* printable_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

int
hx509_revoke_ocsp_print(hx509_context context, const char *path, FILE *out)
{
    struct revoke_ocsp ocsp;
    int ret;
    size_t i;

    if (out == NULL)
	out = stdout;

    memset(&ocsp, 0, sizeof(ocsp));

    ocsp.path = strdup(path);
    if (ocsp.path == NULL)
	return ENOMEM;

    ret = load_ocsp(context, &ocsp);
    if (ret) {
	free_ocsp(&ocsp);
	return ret;
    }

    fprintf(out, "signer: ");

    switch(ocsp.ocsp.tbsResponseData.responderID.element) {
    case choice_OCSPResponderID_byName: {
	hx509_name n;
	char *s;
	_hx509_name_from_Name(&ocsp.ocsp.tbsResponseData.responderID.u.byName, &n);
	hx509_name_to_string(n, &s);
	hx509_name_free(&n);
	fprintf(out, " byName: %s\n", s);
	free(s);
	break;
    }
    case choice_OCSPResponderID_byKey: {
	char *s;
	hex_encode(ocsp.ocsp.tbsResponseData.responderID.u.byKey.data,
		   ocsp.ocsp.tbsResponseData.responderID.u.byKey.length,
		   &s);
	fprintf(out, " byKey: %s\n", s);
	free(s);
	break;
    }
    default:
	_hx509_abort("choice_OCSPResponderID unknown");
	break;
    }

    fprintf(out, "producedAt: %s\n",
	    printable_time(ocsp.ocsp.tbsResponseData.producedAt));

    fprintf(out, "replies: %d\n", ocsp.ocsp.tbsResponseData.responses.len);

    for (i = 0; i < ocsp.ocsp.tbsResponseData.responses.len; i++) {
	const char *status;
	switch (ocsp.ocsp.tbsResponseData.responses.val[i].certStatus.element) {
	case choice_OCSPCertStatus_good:
	    status = "good";
	    break;
	case choice_OCSPCertStatus_revoked:
	    status = "revoked";
	    break;
	case choice_OCSPCertStatus_unknown:
	    status = "unknown";
	    break;
	default:
	    status = "element unknown";
	}

	fprintf(out, "\t%zu. status: %s\n", i, status);

	fprintf(out, "\tthisUpdate: %s\n",
		printable_time(ocsp.ocsp.tbsResponseData.responses.val[i].thisUpdate));
	if (ocsp.ocsp.tbsResponseData.responses.val[i].nextUpdate)
	    fprintf(out, "\tproducedAt: %s\n",
		    printable_time(ocsp.ocsp.tbsResponseData.responses.val[i].thisUpdate));

    }

    fprintf(out, "appended certs:\n");
    if (ocsp.certs)
	ret = hx509_certs_iter_f(context, ocsp.certs, hx509_ci_print_names, out);

    free_ocsp(&ocsp);
    return ret;
}