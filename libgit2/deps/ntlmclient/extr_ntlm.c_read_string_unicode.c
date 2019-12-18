#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  unicode_ctx; } ;
typedef  TYPE_1__ ntlm_client ;
struct TYPE_6__ {size_t pos; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_2__ ntlm_buf ;

/* Variables and functions */
 int ntlm_unicode_utf16_to_8 (char**,size_t*,int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static inline bool read_string_unicode(
	char **out,
	ntlm_client *ntlm,
	ntlm_buf *message,
	uint8_t string_len)
{
	size_t out_len;
	int ret = ntlm_unicode_utf16_to_8(out,
		&out_len,
		ntlm->unicode_ctx,
		(char *)&message->buf[message->pos],
		string_len);

	message->pos += string_len;

	return ret;
}