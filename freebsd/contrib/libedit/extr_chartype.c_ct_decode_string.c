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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {size_t wsize; int /*<<< orphan*/ * wbuff; } ;
typedef  TYPE_1__ ct_buffer_t ;

/* Variables and functions */
 scalar_t__ CT_BUFSIZ ; 
 int ct_conv_wbuff_resize (TYPE_1__*,scalar_t__) ; 
 size_t mbstowcs (int /*<<< orphan*/ *,char const*,size_t) ; 

wchar_t *
ct_decode_string(const char *s, ct_buffer_t *conv)
{
	size_t len;

	if (!s)
		return NULL;

	len = mbstowcs(NULL, s, (size_t)0);
	if (len == (size_t)-1)
		return NULL;

	if (conv->wsize < ++len)
		if (ct_conv_wbuff_resize(conv, len + CT_BUFSIZ) == -1)
			return NULL;

	mbstowcs(conv->wbuff, s, conv->wsize);
	return conv->wbuff;
}