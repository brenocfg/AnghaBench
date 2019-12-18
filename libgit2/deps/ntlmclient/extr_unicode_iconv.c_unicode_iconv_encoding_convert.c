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
typedef  scalar_t__ unicode_iconv_encoding_direction ;
struct TYPE_4__ {int /*<<< orphan*/  ntlm; int /*<<< orphan*/  utf16_to_8; int /*<<< orphan*/  utf8_to_16; } ;
typedef  TYPE_1__ ntlm_unicode_ctx ;
typedef  int /*<<< orphan*/  iconv_t ;

/* Variables and functions */
 scalar_t__ E2BIG ; 
 size_t NTLM_UNICODE_MAX_LEN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t iconv (int /*<<< orphan*/ ,char**,size_t*,char**,size_t*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  ntlm_client_set_errmsg (int /*<<< orphan*/ ,char*) ; 
 char* realloc (char*,size_t) ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  unicode_iconv_init (TYPE_1__*) ; 
 scalar_t__ unicode_iconv_utf8_to_16 ; 

__attribute__((used)) static inline bool unicode_iconv_encoding_convert(
	char **converted,
	size_t *converted_len,
	ntlm_unicode_ctx *ctx,
	const char *string,
	size_t string_len,
	unicode_iconv_encoding_direction direction)
{
	char *in_start, *out_start, *out, *new_out;
	size_t in_start_len, out_start_len, out_size, nul_size, ret, written = 0;
	iconv_t converter;

	*converted = NULL;
	*converted_len = 0;

	if (!unicode_iconv_init(ctx))
		return false;

	/*
	 * When translating UTF8 to UTF16, these strings are only used
	 * internally, and we obey the given length, so we can simply
	 * use a buffer that is 2x the size.  When translating from UTF16
	 * to UTF8, we may need to return to callers, so we need to NUL
	 * terminate and expect an extra byte for UTF8, two for UTF16.
	 */
	if (direction == unicode_iconv_utf8_to_16) {
		converter = ctx->utf8_to_16;
		out_size = (string_len * 2) + 2;
		nul_size = 2;
	} else {
		converter = ctx->utf16_to_8;
		out_size = (string_len / 2) + 1;
		nul_size = 1;
	}

	/* Round to the nearest multiple of 8 */
	out_size = (out_size + 7) & ~7;

	if ((out = malloc(out_size)) == NULL) {
		ntlm_client_set_errmsg(ctx->ntlm, "out of memory");
		return false;
	}

	in_start = (char *)string;
	in_start_len = string_len;

	while (true) {
		out_start = out + written;
		out_start_len = (out_size - nul_size) - written;

		ret = iconv(converter, &in_start, &in_start_len, &out_start, &out_start_len);
		written = (out_size - nul_size) - out_start_len;

		if (ret == 0)
			break;

		if (ret == (size_t)-1 && errno != E2BIG) {
			ntlm_client_set_errmsg(ctx->ntlm, strerror(errno));
			goto on_error;
		}

		/* Grow buffer size by 1.5 (rounded up to a multiple of 8) */
		out_size = ((((out_size << 1) - (out_size >> 1)) + 7) & ~7);

		if (out_size > NTLM_UNICODE_MAX_LEN) {
			ntlm_client_set_errmsg(ctx->ntlm,
				"unicode conversion too large");
			goto on_error;
		}

		if ((new_out = realloc(out, out_size)) == NULL) {
			ntlm_client_set_errmsg(ctx->ntlm, "out of memory");
			goto on_error;
		}

		out = new_out;
	}

	if (in_start_len != 0) {
		ntlm_client_set_errmsg(ctx->ntlm,
			"invalid unicode string; trailing data remains");
		goto on_error;
	}

	/* NUL terminate */
	out[written] = '\0';

	if (direction == unicode_iconv_utf8_to_16)
		out[written + 1] = '\0';

	*converted = out;

	if (converted_len)
		*converted_len = written;

	return true;

on_error:
	free(out);
	return false;
}