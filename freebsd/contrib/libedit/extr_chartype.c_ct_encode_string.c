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
typedef  int ssize_t ;
struct TYPE_4__ {char* cbuff; size_t csize; } ;
typedef  TYPE_1__ ct_buffer_t ;

/* Variables and functions */
 scalar_t__ CT_BUFSIZ ; 
 int /*<<< orphan*/  abort () ; 
 int ct_conv_cbuff_resize (TYPE_1__*,scalar_t__) ; 
 int ct_encode_char (char*,size_t,int /*<<< orphan*/  const) ; 

char *
ct_encode_string(const wchar_t *s, ct_buffer_t *conv)
{
	char *dst;
	ssize_t used;

	if (!s)
		return NULL;

	dst = conv->cbuff;
	for (;;) {
		used = (ssize_t)(dst - conv->cbuff);
		if ((conv->csize - (size_t)used) < 5) {
			if (ct_conv_cbuff_resize(conv,
			    conv->csize + CT_BUFSIZ) == -1)
				return NULL;
			dst = conv->cbuff + used;
		}
		if (!*s)
			break;
		used = ct_encode_char(dst, (size_t)5, *s);
		if (used == -1) /* failed to encode, need more buffer space */
			abort();
		++s;
		dst += used;
	}
	*dst = '\0';
	return conv->cbuff;
}