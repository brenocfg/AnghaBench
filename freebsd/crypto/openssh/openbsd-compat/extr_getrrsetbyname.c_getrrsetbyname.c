#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct rrsetinfo {scalar_t__ rri_rdclass; scalar_t__ rri_rdtype; int rri_nrdatas; int rri_nsigs; struct rdatainfo* rri_sigs; struct rdatainfo* rri_rdatas; int /*<<< orphan*/ * rri_name; int /*<<< orphan*/  rri_flags; int /*<<< orphan*/  rri_ttl; } ;
struct rdatainfo {int /*<<< orphan*/ * rdi_data; int /*<<< orphan*/  rdi_length; } ;
struct dns_rr {scalar_t__ class; scalar_t__ type; int /*<<< orphan*/  size; int /*<<< orphan*/  rdata; struct dns_rr* next; int /*<<< orphan*/  name; int /*<<< orphan*/  ttl; } ;
struct TYPE_4__ {int qdcount; int ancount; int ad; } ;
struct dns_response {struct dns_rr* answer; TYPE_2__ header; TYPE_1__* query; } ;
struct __res_state {int options; } ;
typedef  int /*<<< orphan*/  answer ;
struct TYPE_3__ {scalar_t__ class; scalar_t__ type; } ;

/* Variables and functions */
 int ANSWER_BUFFER_SIZE ; 
 int ERRSET_FAIL ; 
 int ERRSET_INVAL ; 
 int ERRSET_NODATA ; 
 int ERRSET_NOMEMORY ; 
 int ERRSET_NONAME ; 
 int ERRSET_SUCCESS ; 
#define  HOST_NOT_FOUND 129 
#define  NO_DATA 128 
 int RES_DEBUG ; 
 int RES_INIT ; 
 int RES_USE_DNSSEC ; 
 int RES_USE_EDNS0 ; 
 int /*<<< orphan*/  RRSET_VALIDATED ; 
 scalar_t__ T_RRSIG ; 
 struct __res_state* _THREAD_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _res ; 
 void* calloc (int,int) ; 
 void* count_dns_rr (struct dns_rr*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  free_dns_response (struct dns_response*) ; 
 int /*<<< orphan*/  freerrset (struct rrsetinfo*) ; 
 int h_errno ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dns_response* parse_dns_response (int /*<<< orphan*/ *,int) ; 
 int res_init () ; 
 int res_query (char const*,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 

int
getrrsetbyname(const char *hostname, unsigned int rdclass,
    unsigned int rdtype, unsigned int flags,
    struct rrsetinfo **res)
{
	struct __res_state *_resp = _THREAD_PRIVATE(_res, _res, &_res);
	int result;
	struct rrsetinfo *rrset = NULL;
	struct dns_response *response = NULL;
	struct dns_rr *rr;
	struct rdatainfo *rdata;
	int length;
	unsigned int index_ans, index_sig;
	u_char answer[ANSWER_BUFFER_SIZE];

	/* check for invalid class and type */
	if (rdclass > 0xffff || rdtype > 0xffff) {
		result = ERRSET_INVAL;
		goto fail;
	}

	/* don't allow queries of class or type ANY */
	if (rdclass == 0xff || rdtype == 0xff) {
		result = ERRSET_INVAL;
		goto fail;
	}

	/* don't allow flags yet, unimplemented */
	if (flags) {
		result = ERRSET_INVAL;
		goto fail;
	}

	/* initialize resolver */
	if ((_resp->options & RES_INIT) == 0 && res_init() == -1) {
		result = ERRSET_FAIL;
		goto fail;
	}

#ifdef DEBUG
	_resp->options |= RES_DEBUG;
#endif /* DEBUG */

#ifdef RES_USE_DNSSEC
	/* turn on DNSSEC if EDNS0 is configured */
	if (_resp->options & RES_USE_EDNS0)
		_resp->options |= RES_USE_DNSSEC;
#endif /* RES_USE_DNSEC */

	/* make query */
	length = res_query(hostname, (signed int) rdclass, (signed int) rdtype,
	    answer, sizeof(answer));
	if (length < 0) {
		switch(h_errno) {
		case HOST_NOT_FOUND:
			result = ERRSET_NONAME;
			goto fail;
		case NO_DATA:
			result = ERRSET_NODATA;
			goto fail;
		default:
			result = ERRSET_FAIL;
			goto fail;
		}
	}

	/* parse result */
	response = parse_dns_response(answer, length);
	if (response == NULL) {
		result = ERRSET_FAIL;
		goto fail;
	}

	if (response->header.qdcount != 1) {
		result = ERRSET_FAIL;
		goto fail;
	}

	/* initialize rrset */
	rrset = calloc(1, sizeof(struct rrsetinfo));
	if (rrset == NULL) {
		result = ERRSET_NOMEMORY;
		goto fail;
	}
	rrset->rri_rdclass = response->query->class;
	rrset->rri_rdtype = response->query->type;
	rrset->rri_ttl = response->answer->ttl;
	rrset->rri_nrdatas = response->header.ancount;

#ifdef HAVE_HEADER_AD
	/* check for authenticated data */
	if (response->header.ad == 1)
		rrset->rri_flags |= RRSET_VALIDATED;
#endif

	/* copy name from answer section */
	rrset->rri_name = strdup(response->answer->name);
	if (rrset->rri_name == NULL) {
		result = ERRSET_NOMEMORY;
		goto fail;
	}

	/* count answers */
	rrset->rri_nrdatas = count_dns_rr(response->answer, rrset->rri_rdclass,
	    rrset->rri_rdtype);
	rrset->rri_nsigs = count_dns_rr(response->answer, rrset->rri_rdclass,
	    T_RRSIG);

	/* allocate memory for answers */
	rrset->rri_rdatas = calloc(rrset->rri_nrdatas,
	    sizeof(struct rdatainfo));
	if (rrset->rri_rdatas == NULL) {
		result = ERRSET_NOMEMORY;
		goto fail;
	}

	/* allocate memory for signatures */
	if (rrset->rri_nsigs > 0) {
		rrset->rri_sigs = calloc(rrset->rri_nsigs, sizeof(struct rdatainfo));
		if (rrset->rri_sigs == NULL) {
			result = ERRSET_NOMEMORY;
			goto fail;
		}
	}

	/* copy answers & signatures */
	for (rr = response->answer, index_ans = 0, index_sig = 0;
	    rr; rr = rr->next) {

		rdata = NULL;

		if (rr->class == rrset->rri_rdclass &&
		    rr->type  == rrset->rri_rdtype)
			rdata = &rrset->rri_rdatas[index_ans++];

		if (rr->class == rrset->rri_rdclass &&
		    rr->type  == T_RRSIG)
			rdata = &rrset->rri_sigs[index_sig++];

		if (rdata) {
			rdata->rdi_length = rr->size;
			rdata->rdi_data   = malloc(rr->size);

			if (rdata->rdi_data == NULL) {
				result = ERRSET_NOMEMORY;
				goto fail;
			}
			memcpy(rdata->rdi_data, rr->rdata, rr->size);
		}
	}
	free_dns_response(response);

	*res = rrset;
	return (ERRSET_SUCCESS);

fail:
	if (rrset != NULL)
		freerrset(rrset);
	if (response != NULL)
		free_dns_response(response);
	return (result);
}