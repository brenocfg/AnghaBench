#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int responseStatus; TYPE_2__* responseBytes; } ;
struct TYPE_6__ {size_t length; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {TYPE_1__ response; int /*<<< orphan*/  responseType; } ;
typedef  TYPE_3__ OCSPResponse ;
typedef  int /*<<< orphan*/  OCSPBasicOCSPResponse ;

/* Variables and functions */
 int ASN1_EXTRA_DATA ; 
 int EINVAL ; 
 int HX509_REVOKE_WRONG_DATA ; 
 int /*<<< orphan*/  asn1_oid_id_pkix_ocsp_basic ; 
 int decode_OCSPBasicOCSPResponse (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int decode_OCSPResponse (void const*,size_t,TYPE_3__*,size_t*) ; 
 int der_heim_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_OCSPBasicOCSPResponse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_OCSPResponse (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
#define  successful 128 

__attribute__((used)) static int
parse_ocsp_basic(const void *data, size_t length, OCSPBasicOCSPResponse *basic)
{
    OCSPResponse resp;
    size_t size;
    int ret;

    memset(basic, 0, sizeof(*basic));

    ret = decode_OCSPResponse(data, length, &resp, &size);
    if (ret)
	return ret;
    if (length != size) {
	free_OCSPResponse(&resp);
	return ASN1_EXTRA_DATA;
    }

    switch (resp.responseStatus) {
    case successful:
	break;
    default:
	free_OCSPResponse(&resp);
	return HX509_REVOKE_WRONG_DATA;
    }

    if (resp.responseBytes == NULL) {
	free_OCSPResponse(&resp);
	return EINVAL;
    }

    ret = der_heim_oid_cmp(&resp.responseBytes->responseType,
			   &asn1_oid_id_pkix_ocsp_basic);
    if (ret != 0) {
	free_OCSPResponse(&resp);
	return HX509_REVOKE_WRONG_DATA;
    }

    ret = decode_OCSPBasicOCSPResponse(resp.responseBytes->response.data,
				       resp.responseBytes->response.length,
				       basic,
				       &size);
    if (ret) {
	free_OCSPResponse(&resp);
	return ret;
    }
    if (size != resp.responseBytes->response.length) {
	free_OCSPResponse(&resp);
	free_OCSPBasicOCSPResponse(basic);
	return ASN1_EXTRA_DATA;
    }
    free_OCSPResponse(&resp);

    return 0;
}