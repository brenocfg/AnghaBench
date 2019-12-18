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

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  B ; 
#define  EAD_TYPE_GET_PRIME 130 
#define  EAD_TYPE_SEND_A 129 
#define  EAD_TYPE_SET_USERNAME 128 
 int /*<<< orphan*/  ead_set_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_password () ; 
 int /*<<< orphan*/  skey ; 
 int state ; 
 int /*<<< orphan*/  t_serverclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t_servergenexp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t_servergetkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * t_serveropenraw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tce ; 
 int /*<<< orphan*/  tpe ; 
 int /*<<< orphan*/ * ts ; 

__attribute__((used)) static void
set_state(int nstate)
{
	if (state == nstate)
		return;

	if (nstate < state) {
		if ((nstate < EAD_TYPE_GET_PRIME) &&
			(state >= EAD_TYPE_GET_PRIME)) {
			t_serverclose(ts);
			ts = NULL;
		}
		goto done;
	}

	switch(state) {
	case EAD_TYPE_SET_USERNAME:
		if (!prepare_password())
			goto error;
		ts = t_serveropenraw(&tpe, tce);
		if (!ts)
			goto error;
		break;
	case EAD_TYPE_GET_PRIME:
		B = t_servergenexp(ts);
		break;
	case EAD_TYPE_SEND_A:
		skey = t_servergetkey(ts, &A);
		if (!skey)
			goto error;

		ead_set_key(skey);
		break;
	}
done:
	state = nstate;
error:
	return;
}