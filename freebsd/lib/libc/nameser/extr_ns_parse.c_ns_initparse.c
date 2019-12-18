#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ns_sect ;
struct TYPE_4__ {scalar_t__ _id; scalar_t__ _flags; scalar_t__* _counts; int /*<<< orphan*/  const** _sections; int /*<<< orphan*/  const* _eom; int /*<<< orphan*/  const* _msg; } ;
typedef  TYPE_1__ ns_msg ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  NS_GET16 (scalar_t__,int /*<<< orphan*/  const*) ; 
 int NS_INT16SZ ; 
 int /*<<< orphan*/  RETERR (int /*<<< orphan*/ ) ; 
 int ns_s_max ; 
 int ns_skiprr (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  setsection (TYPE_1__*,int) ; 

int
ns_initparse(const u_char *msg, int msglen, ns_msg *handle) {
	const u_char *eom = msg + msglen;
	int i;

	handle->_msg = msg;
	handle->_eom = eom;
	if (msg + NS_INT16SZ > eom)
		RETERR(EMSGSIZE);
	NS_GET16(handle->_id, msg);
	if (msg + NS_INT16SZ > eom)
		RETERR(EMSGSIZE);
	NS_GET16(handle->_flags, msg);
	for (i = 0; i < ns_s_max; i++) {
		if (msg + NS_INT16SZ > eom)
			RETERR(EMSGSIZE);
		NS_GET16(handle->_counts[i], msg);
	}
	for (i = 0; i < ns_s_max; i++)
		if (handle->_counts[i] == 0)
			handle->_sections[i] = NULL;
		else {
			int b = ns_skiprr(msg, eom, (ns_sect)i,
					  handle->_counts[i]);

			if (b < 0)
				return (-1);
			handle->_sections[i] = msg;
			msg += b;
		}
	if (msg != eom)
		RETERR(EMSGSIZE);
	setsection(handle, ns_s_max);
	return (0);
}