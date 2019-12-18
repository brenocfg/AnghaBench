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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ntlm_client ;
struct TYPE_3__ {int len; int pos; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ ntlm_buf ;

/* Variables and functions */
 int /*<<< orphan*/  ntlm_client_set_errmsg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline bool read_byte(
	uint8_t *out,
	ntlm_client *ntlm,
	ntlm_buf *message)
{
	if (message->len - message->pos < 1) {
		ntlm_client_set_errmsg(ntlm, "truncated message");
		return false;
	}

	*out = message->buf[message->pos++];
	return true;
}