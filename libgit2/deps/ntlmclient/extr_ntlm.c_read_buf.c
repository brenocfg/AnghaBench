#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ntlm_client ;
struct TYPE_3__ {size_t len; size_t pos; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ ntlm_buf ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ntlm_client_set_errmsg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline bool read_buf(
	unsigned char *out,
	ntlm_client *ntlm,
	ntlm_buf *message,
	size_t len)
{
	if (message->len - message->pos < len) {
		ntlm_client_set_errmsg(ntlm, "truncated message");
		return false;
	}

	memcpy(out, &message->buf[message->pos], len);
	message->pos += len;

	return true;
}