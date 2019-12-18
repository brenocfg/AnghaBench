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
typedef  size_t u_int ;
typedef  int u_char ;
struct ctl_var {int flags; size_t code; char* text; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CERR_BADVALUE ; 
 int /*<<< orphan*/  CERR_UNKNOWNVAR ; 
 int CS_MAXCODE ; 
 int DEF ; 
 int EOV ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int count_var (struct ctl_var*) ; 
 int /*<<< orphan*/  ctl_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_flushpkt (int /*<<< orphan*/ ) ; 
 struct ctl_var* ctl_getitem (struct ctl_var*,char**) ; 
 int /*<<< orphan*/  ctl_putdata (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_putsys (int) ; 
 scalar_t__ ctl_sys_num_events ; 
 int /*<<< orphan*/  ctlsysstatus () ; 
 int* def_sys_var ; 
 int* emalloc_zero (size_t) ; 
 struct ctl_var* ext_sys_var ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ res_authokay ; 
 TYPE_1__ rpkt ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 struct ctl_var* sys_var ; 

__attribute__((used)) static void
read_sysvars(void)
{
	const struct ctl_var *v;
	struct ctl_var *kv;
	u_int	n;
	u_int	gotvar;
	const u_char *cs;
	char *	valuep;
	const char * pch;
	u_char *wants;
	size_t	wants_count;

	/*
	 * Wants system variables. Figure out which he wants
	 * and give them to him.
	 */
	rpkt.status = htons(ctlsysstatus());
	if (res_authokay)
		ctl_sys_num_events = 0;
	wants_count = CS_MAXCODE + 1 + count_var(ext_sys_var);
	wants = emalloc_zero(wants_count);
	gotvar = 0;
	while (NULL != (v = ctl_getitem(sys_var, &valuep))) {
		if (!(EOV & v->flags)) {
			INSIST(v->code < wants_count);
			wants[v->code] = 1;
			gotvar = 1;
		} else {
			v = ctl_getitem(ext_sys_var, &valuep);
			if (NULL == v) {
				ctl_error(CERR_BADVALUE);
				free(wants);
				return;
			}
			if (EOV & v->flags) {
				ctl_error(CERR_UNKNOWNVAR);
				free(wants);
				return;
			}
			n = v->code + CS_MAXCODE + 1;
			INSIST(n < wants_count);
			wants[n] = 1;
			gotvar = 1;
		}
	}
	if (gotvar) {
		for (n = 1; n <= CS_MAXCODE; n++)
			if (wants[n])
				ctl_putsys(n);
		for (n = 0; n + CS_MAXCODE + 1 < wants_count; n++)
			if (wants[n + CS_MAXCODE + 1]) {
				pch = ext_sys_var[n].text;
				ctl_putdata(pch, strlen(pch), 0);
			}
	} else {
		for (cs = def_sys_var; *cs != 0; cs++)
			ctl_putsys((int)*cs);
		for (kv = ext_sys_var; kv && !(EOV & kv->flags); kv++)
			if (DEF & kv->flags)
				ctl_putdata(kv->text, strlen(kv->text),
					    0);
	}
	free(wants);
	ctl_flushpkt(0);
}