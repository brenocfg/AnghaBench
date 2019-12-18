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
typedef  int uint32_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct uni_ie_traffic {int dummy; } ;
struct uni_ie_qos {int dummy; } ;
struct uni_ie_mdcr {int dummy; } ;
struct uni_ie_exqos {int dummy; } ;
struct uni_ie_epref {int dummy; } ;
struct uni_ie_eetd {int dummy; } ;
struct uni_ie_connid {int dummy; } ;
struct uni_ie_connedsub {int dummy; } ;
struct uni_ie_conned {int dummy; } ;
struct uni_ie_callingsub {int dummy; } ;
struct uni_ie_calling {int dummy; } ;
struct uni_ie_calledsub {int dummy; } ;
struct uni_ie_called {int dummy; } ;
struct uni_ie_blli {int dummy; } ;
struct uni_ie_bearer {int dummy; } ;
struct uni_ie_abrsetup {int dummy; } ;
struct uni_ie_abradd {int dummy; } ;
struct uni_ie_aal {int dummy; } ;
struct ccuser {int dummy; } ;
struct ccconn {int /*<<< orphan*/  mdcr; int /*<<< orphan*/  connid; int /*<<< orphan*/  abradd; int /*<<< orphan*/  abrsetup; int /*<<< orphan*/  eetd; int /*<<< orphan*/  connedsub; int /*<<< orphan*/  conned; int /*<<< orphan*/  epref; int /*<<< orphan*/  aal; int /*<<< orphan*/  callingsub; int /*<<< orphan*/  calling; int /*<<< orphan*/  calledsub; int /*<<< orphan*/  called; int /*<<< orphan*/  exqos; int /*<<< orphan*/  qos; int /*<<< orphan*/  traffic; int /*<<< orphan*/  bearer; int /*<<< orphan*/  blli_selector; int /*<<< orphan*/ * blli; } ;
typedef  enum atm_attribute { ____Placeholder_atm_attribute } atm_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  ATMERR_BAD_ATTR ; 
 int /*<<< orphan*/  ATMRESP_ATTRS ; 
#define  ATM_ATTR_AAL 147 
#define  ATM_ATTR_ABRADD 146 
#define  ATM_ATTR_ABRSETUP 145 
#define  ATM_ATTR_BEARER 144 
#define  ATM_ATTR_BLLI 143 
#define  ATM_ATTR_BLLI_SELECTOR 142 
#define  ATM_ATTR_CALLED 141 
#define  ATM_ATTR_CALLEDSUB 140 
#define  ATM_ATTR_CALLING 139 
#define  ATM_ATTR_CALLINGSUB 138 
#define  ATM_ATTR_CONNED 137 
#define  ATM_ATTR_CONNEDSUB 136 
#define  ATM_ATTR_CONNID 135 
#define  ATM_ATTR_EETD 134 
#define  ATM_ATTR_EPREF 133 
#define  ATM_ATTR_EXQOS 132 
#define  ATM_ATTR_MDCR 131 
#define  ATM_ATTR_NONE 130 
#define  ATM_ATTR_QOS 129 
#define  ATM_ATTR_TRAFFIC 128 
 int /*<<< orphan*/  CCFREE (void*) ; 
 void* CCMALLOC (size_t) ; 
 int /*<<< orphan*/  cc_user_err (struct ccuser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_user_ok (struct ccuser*,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
cc_attr_query(struct ccuser *user, struct ccconn *conn,
    uint32_t *attr, u_int count)
{
	void *val, *ptr;
	size_t total, len;
	u_int i;
	uint32_t *atab;

	/* determine the length of the total attribute buffer */
	total = sizeof(uint32_t) + count * sizeof(uint32_t);
	for (i = 0; i < count; i++) {
		len = 0;
		switch ((enum atm_attribute)attr[i]) {

		  case ATM_ATTR_NONE:
			break;

		  case ATM_ATTR_BLLI_SELECTOR:
			len = sizeof(uint32_t);
			break;

		  case ATM_ATTR_BLLI:
			len = sizeof(struct uni_ie_blli);
			break;

		  case ATM_ATTR_BEARER:
			len = sizeof(struct uni_ie_bearer);
			break;

		  case ATM_ATTR_TRAFFIC:
			len = sizeof(struct uni_ie_traffic);
			break;

		  case ATM_ATTR_QOS:
			len = sizeof(struct uni_ie_qos);
			break;

		  case ATM_ATTR_EXQOS:
			len = sizeof(struct uni_ie_exqos);
			break;

		  case ATM_ATTR_CALLED:
			len = sizeof(struct uni_ie_called);
			break;

		  case ATM_ATTR_CALLEDSUB:
			len = sizeof(struct uni_ie_calledsub);
			break;

		  case ATM_ATTR_CALLING:
			len = sizeof(struct uni_ie_calling);
			break;

		  case ATM_ATTR_CALLINGSUB:
			len = sizeof(struct uni_ie_callingsub);
			break;

		  case ATM_ATTR_AAL:
			len = sizeof(struct uni_ie_aal);
			break;

		  case ATM_ATTR_EPREF:
			len = sizeof(struct uni_ie_epref);
			break;

		  case ATM_ATTR_CONNED:
			len = sizeof(struct uni_ie_conned);
			break;

		  case ATM_ATTR_CONNEDSUB:
			len = sizeof(struct uni_ie_connedsub);
			break;

		  case ATM_ATTR_EETD:
			len = sizeof(struct uni_ie_eetd);
			break;

		  case ATM_ATTR_ABRSETUP:
			len = sizeof(struct uni_ie_abrsetup);
			break;

		  case ATM_ATTR_ABRADD:
			len = sizeof(struct uni_ie_abradd);
			break;

		  case ATM_ATTR_CONNID:
			len = sizeof(struct uni_ie_connid);
			break;

		  case ATM_ATTR_MDCR:
			len = sizeof(struct uni_ie_mdcr);
			break;
		}
		if (len == 0) {
			cc_user_err(user, ATMERR_BAD_ATTR);
			return;
		}
		total += len;
	}

	/* allocate buffer */
	val = CCMALLOC(total);
	if (val == NULL)
		return;

	atab = val;
	atab[0] = count;

	/* fill */
	ptr = (u_char *)val + (sizeof(uint32_t) + count * sizeof(uint32_t));
	for (i = 0; i < count; i++) {
		len = 0;
		atab[i + 1] = attr[i];
		switch (attr[i]) {

		  case ATM_ATTR_NONE:
			break;

		  case ATM_ATTR_BLLI_SELECTOR:
			len = sizeof(uint32_t);
			memcpy(ptr, &conn->blli_selector, len);
			break;

		  case ATM_ATTR_BLLI:
			/* in A6 the blli_selector may be 0 when
			 * there was no blli in the SETUP.
			 */
			len = sizeof(struct uni_ie_blli);
			if (conn->blli_selector == 0)
				memset(ptr, 0, len);
			else
				memcpy(ptr, &conn->blli[conn->blli_selector -
				    1], len);
			break;

		  case ATM_ATTR_BEARER:
			len = sizeof(struct uni_ie_bearer);
			memcpy(ptr, &conn->bearer, len);
			break;

		  case ATM_ATTR_TRAFFIC:
			len = sizeof(struct uni_ie_traffic);
			memcpy(ptr, &conn->traffic, len);
			break;

		  case ATM_ATTR_QOS:
			len = sizeof(struct uni_ie_qos);
			memcpy(ptr, &conn->qos, len);
			break;

		  case ATM_ATTR_EXQOS:
			len = sizeof(struct uni_ie_exqos);
			memcpy(ptr, &conn->exqos, len);
			break;

		  case ATM_ATTR_CALLED:
			len = sizeof(struct uni_ie_called);
			memcpy(ptr, &conn->called, len);
			break;

		  case ATM_ATTR_CALLEDSUB:
			len = sizeof(struct uni_ie_calledsub);
			memcpy(ptr, &conn->calledsub, len);
			break;

		  case ATM_ATTR_CALLING:
			len = sizeof(struct uni_ie_calling);
			memcpy(ptr, &conn->calling, len);
			break;

		  case ATM_ATTR_CALLINGSUB:
			len = sizeof(struct uni_ie_callingsub);
			memcpy(ptr, &conn->callingsub, len);
			break;

		  case ATM_ATTR_AAL:
			len = sizeof(struct uni_ie_aal);
			memcpy(ptr, &conn->aal, len);
			break;

		  case ATM_ATTR_EPREF:
			len = sizeof(struct uni_ie_epref);
			memcpy(ptr, &conn->epref, len);
			break;

		  case ATM_ATTR_CONNED:
			len = sizeof(struct uni_ie_conned);
			memcpy(ptr, &conn->conned, len);
			break;

		  case ATM_ATTR_CONNEDSUB:
			len = sizeof(struct uni_ie_connedsub);
			memcpy(ptr, &conn->connedsub, len);
			break;

		  case ATM_ATTR_EETD:
			len = sizeof(struct uni_ie_eetd);
			memcpy(ptr, &conn->eetd, len);
			break;

		  case ATM_ATTR_ABRSETUP:
			len = sizeof(struct uni_ie_abrsetup);
			memcpy(ptr, &conn->abrsetup, len);
			break;

		  case ATM_ATTR_ABRADD:
			len = sizeof(struct uni_ie_abradd);
			memcpy(ptr, &conn->abradd, len);
			break;

		  case ATM_ATTR_CONNID:
			len = sizeof(struct uni_ie_connid);
			memcpy(ptr, &conn->connid, len);
			break;

		  case ATM_ATTR_MDCR:
			len = sizeof(struct uni_ie_mdcr);
			memcpy(ptr, &conn->mdcr, len);
			break;
		}
		ptr = (u_char *)ptr + len;
	}

	cc_user_ok(user, ATMRESP_ATTRS, val, total);

	CCFREE(val);
}