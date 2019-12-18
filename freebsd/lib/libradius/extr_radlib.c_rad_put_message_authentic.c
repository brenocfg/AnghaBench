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
typedef  int /*<<< orphan*/  u_char ;
struct rad_handle {scalar_t__* out; scalar_t__ authentic_pos; scalar_t__ out_len; } ;
typedef  int /*<<< orphan*/  md_zero ;

/* Variables and functions */
 int MD5_DIGEST_LENGTH ; 
 size_t POS_CODE ; 
 scalar_t__ RAD_ACCOUNTING_REQUEST ; 
 int /*<<< orphan*/  RAD_MESSAGE_AUTHENTIC ; 
 int /*<<< orphan*/  generr (struct rad_handle*,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int put_raw_attr (struct rad_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
rad_put_message_authentic(struct rad_handle *h)
{
#ifdef WITH_SSL
	u_char md_zero[MD5_DIGEST_LENGTH];

	if (h->out[POS_CODE] == RAD_ACCOUNTING_REQUEST) {
		generr(h, "Message-Authenticator is not valid"
		    " in accounting requests");
		return -1;
	}

	if (h->authentic_pos == 0) {
		h->authentic_pos = h->out_len;
		memset(md_zero, 0, sizeof(md_zero));
		return (put_raw_attr(h, RAD_MESSAGE_AUTHENTIC, md_zero,
		    sizeof(md_zero)));
	}
	return 0;
#else
	generr(h, "Message Authenticator not supported,"
	    " please recompile libradius with SSL support");
	return -1;
#endif
}