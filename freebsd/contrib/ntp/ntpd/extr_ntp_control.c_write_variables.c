#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct recvbuf {int dummy; } ;
struct ctl_var {int flags; char* text; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CAN_WRITE ; 
 int /*<<< orphan*/  CERR_BADFMT ; 
 int /*<<< orphan*/  CERR_BADVALUE ; 
 int /*<<< orphan*/  CERR_PERMISSION ; 
 int /*<<< orphan*/  CERR_UNKNOWNVAR ; 
 int /*<<< orphan*/  CERR_UNSPEC ; 
 int EOV ; 
 long LEAP_NOTINSYNC ; 
 scalar_t__ atoint (char*,long*) ; 
 int /*<<< orphan*/  ctl_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_flushpkt (int /*<<< orphan*/ ) ; 
 struct ctl_var* ctl_getitem (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  ctlsysstatus () ; 
 char* emalloc (size_t) ; 
 int /*<<< orphan*/  ext_sys_var ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ res_associd ; 
 TYPE_1__ rpkt ; 
 int /*<<< orphan*/  set_sys_var (char*,int,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  sys_var ; 

__attribute__((used)) static void
write_variables(
	struct recvbuf *rbufp,
	int restrict_mask
	)
{
	const struct ctl_var *v;
	int ext_var;
	char *valuep;
	long val;
	size_t octets;
	char *vareqv;
	const char *t;
	char *tt;

	val = 0;
	/*
	 * If he's trying to write into a peer tell him no way
	 */
	if (res_associd != 0) {
		ctl_error(CERR_PERMISSION);
		return;
	}

	/*
	 * Set status
	 */
	rpkt.status = htons(ctlsysstatus());

	/*
	 * Look through the variables. Dump out at the first sign of
	 * trouble.
	 */
	while ((v = ctl_getitem(sys_var, &valuep)) != NULL) {
		ext_var = 0;
		if (v->flags & EOV) {
			v = ctl_getitem(ext_sys_var, &valuep);
			if (v != NULL) {
				if (v->flags & EOV) {
					ctl_error(CERR_UNKNOWNVAR);
					return;
				}
				ext_var = 1;
			} else {
				break;
			}
		}
		if (!(v->flags & CAN_WRITE)) {
			ctl_error(CERR_PERMISSION);
			return;
		}
		/* [bug 3565] writing makes sense only if we *have* a
		 * value in the packet!
		 */
		if (valuep == NULL) {
			ctl_error(CERR_BADFMT);
			return;
		}
		if (!ext_var) {
			if ( !(*valuep && atoint(valuep, &val))) {
				ctl_error(CERR_BADFMT);
				return;
			}
			if ((val & ~LEAP_NOTINSYNC) != 0) {
				ctl_error(CERR_BADVALUE);
				return;
			}
		}
		
		if (ext_var) {
			octets = strlen(v->text) + strlen(valuep) + 2;
			vareqv = emalloc(octets);
			tt = vareqv;
			t = v->text;
			while (*t && *t != '=')
				*tt++ = *t++;
			*tt++ = '=';
			memcpy(tt, valuep, 1 + strlen(valuep));
			set_sys_var(vareqv, 1 + strlen(vareqv), v->flags);
			free(vareqv);
		} else {
			ctl_error(CERR_UNSPEC); /* really */
			return;
		}
	}

	/*
	 * If we got anything, do it. xxx nothing to do ***
	 */
	/*
	  if (leapind != ~0 || leapwarn != ~0) {
	  if (!leap_setleap((int)leapind, (int)leapwarn)) {
	  ctl_error(CERR_PERMISSION);
	  return;
	  }
	  }
	*/
	ctl_flushpkt(0);
}