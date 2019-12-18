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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t u_int ;
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
struct ccconn {int /*<<< orphan*/  mdcr; int /*<<< orphan*/  dirty_attr; int /*<<< orphan*/  connid; int /*<<< orphan*/  abradd; int /*<<< orphan*/  abrsetup; int /*<<< orphan*/  eetd; int /*<<< orphan*/  aal; int /*<<< orphan*/  callingsub; int /*<<< orphan*/  calling; int /*<<< orphan*/  calledsub; int /*<<< orphan*/  exqos; int /*<<< orphan*/  qos; int /*<<< orphan*/  traffic; int /*<<< orphan*/  bearer; int /*<<< orphan*/  blli_selector; int /*<<< orphan*/ * blli; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  sel ;
typedef  enum atm_attribute { ____Placeholder_atm_attribute } atm_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  ATMERR_BAD_ARGS ; 
 int /*<<< orphan*/  ATMERR_BAD_ATTR ; 
 int /*<<< orphan*/  ATMERR_BAD_VALUE ; 
 int /*<<< orphan*/  ATMERR_RDONLY ; 
 int /*<<< orphan*/  ATMRESP_NONE ; 
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
 int /*<<< orphan*/  CCDIRTY_AAL ; 
 int /*<<< orphan*/  CCDIRTY_ABRADD ; 
 int /*<<< orphan*/  CCDIRTY_ABRSETUP ; 
 int /*<<< orphan*/  CCDIRTY_BLLI ; 
 int /*<<< orphan*/  CCDIRTY_CONNID ; 
 int /*<<< orphan*/  CCDIRTY_EETD ; 
 int /*<<< orphan*/  CCDIRTY_EXQOS ; 
 int /*<<< orphan*/  CCDIRTY_TRAFFIC ; 
 int /*<<< orphan*/  CONN_OUT_PREPARING ; 
 int /*<<< orphan*/  UNI_NUM_IE_BLLI ; 
 int /*<<< orphan*/  cc_user_err (struct ccuser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_user_ok (struct ccuser*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
cc_attr_set(struct ccuser *user, struct ccconn *conn, uint32_t *attr,
    u_int count, u_char *val, size_t vallen)
{
	size_t total, len;
	u_int i;
	u_char *ptr;

	/* determine the length of the total attribute buffer */
	total = 0;
	ptr = val;
	for (i = 0; i < count; i++) {
		len = 0;
		switch ((enum atm_attribute)attr[i]) {

		  case ATM_ATTR_NONE:
			break;

		  case ATM_ATTR_BLLI_SELECTOR:
		    {
			uint32_t sel;

			if (conn->state != CONN_OUT_PREPARING)
				goto rdonly;
			memcpy(&sel, ptr, sizeof(sel));
			if (sel == 0 || sel > UNI_NUM_IE_BLLI)
				goto bad_val;
			len = sizeof(uint32_t);
			break;
		    }

		  case ATM_ATTR_BLLI:
			len = sizeof(struct uni_ie_blli);
			break;

		  case ATM_ATTR_BEARER:
			if (conn->state != CONN_OUT_PREPARING)
				goto rdonly;
			len = sizeof(struct uni_ie_bearer);
			break;

		  case ATM_ATTR_TRAFFIC:
			len = sizeof(struct uni_ie_traffic);
			break;

		  case ATM_ATTR_QOS:
			if (conn->state != CONN_OUT_PREPARING)
				goto rdonly;
			len = sizeof(struct uni_ie_qos);
			break;

		  case ATM_ATTR_EXQOS:
			len = sizeof(struct uni_ie_exqos);
			break;

		  case ATM_ATTR_CALLED:
			goto rdonly;

		  case ATM_ATTR_CALLEDSUB:
			if (conn->state != CONN_OUT_PREPARING)
				goto rdonly;
			len = sizeof(struct uni_ie_calledsub);
			break;

		  case ATM_ATTR_CALLING:
			if (conn->state != CONN_OUT_PREPARING)
				goto rdonly;
			len = sizeof(struct uni_ie_calling);
			break;

		  case ATM_ATTR_CALLINGSUB:
			if (conn->state != CONN_OUT_PREPARING)
				goto rdonly;
			len = sizeof(struct uni_ie_callingsub);
			break;

		  case ATM_ATTR_AAL:
			len = sizeof(struct uni_ie_aal);
			break;

		  case ATM_ATTR_EPREF:
			goto rdonly;

		  case ATM_ATTR_CONNED:
			goto rdonly;

		  case ATM_ATTR_CONNEDSUB:
			goto rdonly;

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
			if (conn->state != CONN_OUT_PREPARING)
				goto rdonly;
			len = sizeof(struct uni_ie_mdcr);
			break;
		}
		if (len == 0) {
			cc_user_err(user, ATMERR_BAD_ATTR);
			return;
		}
		total += len;
		ptr += len;
	}

	/* check the length */
	if (vallen != total) {
		cc_user_err(user, ATMERR_BAD_ARGS);
		return;
	}

	ptr = val;
	for (i = 0; i < count; i++) {
		len = 0;
		switch ((enum atm_attribute)attr[i]) {

		  case ATM_ATTR_NONE:
			break;

		  case ATM_ATTR_BLLI_SELECTOR:
		    {
			uint32_t sel;

			memcpy(&sel, ptr, sizeof(sel));
			conn->blli_selector = sel;
			len = sizeof(uint32_t);
			break;
		    }

		  case ATM_ATTR_BLLI:
			len = sizeof(struct uni_ie_blli);
			memcpy(&conn->blli[conn->blli_selector - 1], ptr, len);
			conn->dirty_attr |= CCDIRTY_BLLI;
			break;

		  case ATM_ATTR_BEARER:
			len = sizeof(struct uni_ie_bearer);
			memcpy(&conn->bearer, ptr, len);
			break;

		  case ATM_ATTR_TRAFFIC:
			len = sizeof(struct uni_ie_traffic);
			memcpy(&conn->traffic, ptr, len);
			conn->dirty_attr |= CCDIRTY_TRAFFIC;
			break;

		  case ATM_ATTR_QOS:
			len = sizeof(struct uni_ie_qos);
			memcpy(&conn->qos, ptr, len);
			break;

		  case ATM_ATTR_EXQOS:
			len = sizeof(struct uni_ie_exqos);
			memcpy(&conn->exqos, ptr, len);
			conn->dirty_attr |= CCDIRTY_EXQOS;
			break;

		  case ATM_ATTR_CALLED:
			len = sizeof(struct uni_ie_called);
			break;

		  case ATM_ATTR_CALLEDSUB:
			len = sizeof(struct uni_ie_calledsub);
			memcpy(&conn->calledsub, ptr, len);
			break;

		  case ATM_ATTR_CALLING:
			len = sizeof(struct uni_ie_calling);
			memcpy(&conn->calling, ptr, len);
			break;

		  case ATM_ATTR_CALLINGSUB:
			len = sizeof(struct uni_ie_callingsub);
			memcpy(&conn->callingsub, ptr, len);
			break;

		  case ATM_ATTR_AAL:
			len = sizeof(struct uni_ie_aal);
			memcpy(&conn->aal, ptr, len);
			conn->dirty_attr |= CCDIRTY_AAL;
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
			memcpy(&conn->eetd, ptr, len);
			conn->dirty_attr |= CCDIRTY_EETD;
			break;

		  case ATM_ATTR_ABRSETUP:
			len = sizeof(struct uni_ie_abrsetup);
			memcpy(&conn->abrsetup, ptr, len);
			conn->dirty_attr |= CCDIRTY_ABRSETUP;
			break;

		  case ATM_ATTR_ABRADD:
			len = sizeof(struct uni_ie_abradd);
			memcpy(&conn->abradd, ptr, len);
			conn->dirty_attr |= CCDIRTY_ABRADD;
			break;

		  case ATM_ATTR_CONNID:
			len = sizeof(struct uni_ie_connid);
			memcpy(&conn->connid, ptr, len);
			conn->dirty_attr |= CCDIRTY_CONNID;
			break;

		  case ATM_ATTR_MDCR:
			len = sizeof(struct uni_ie_mdcr);
			memcpy(&conn->mdcr, ptr, len);
			break;
		}
		ptr += len;
	}

	cc_user_ok(user, ATMRESP_NONE, NULL, 0);
	return;

  bad_val:
	cc_user_err(user, ATMERR_BAD_VALUE);
	return;

  rdonly:
	cc_user_err(user, ATMERR_RDONLY);
	return;
}