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
typedef  scalar_t__ unicode_builtin_encoding_direction ;
struct TYPE_3__ {int /*<<< orphan*/  ntlm; } ;
typedef  TYPE_1__ ntlm_unicode_ctx ;
typedef  int /*<<< orphan*/  UTF8 ;
typedef  int /*<<< orphan*/  UTF16 ;
typedef  int ConversionResult ;

/* Variables and functions */
 int ConvertUTF16toUTF8 (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ConvertUTF8toUTF16 (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t NTLM_UNICODE_MAX_LEN ; 
#define  conversionOK 131 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lenientConversion ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  ntlm_client_set_errmsg (int /*<<< orphan*/ ,char*) ; 
 char* realloc (char*,size_t) ; 
#define  sourceExhausted 130 
#define  sourceIllegal 129 
 int /*<<< orphan*/  strictConversion ; 
#define  targetExhausted 128 
 scalar_t__ unicode_builtin_utf16_to_8 ; 
 scalar_t__ unicode_builtin_utf8_to_16 ; 

__attribute__((used)) static inline bool unicode_builtin_encoding_convert(
	char **converted,
	size_t *converted_len,
	ntlm_unicode_ctx *ctx,
	const char *string,
	size_t string_len,
	unicode_builtin_encoding_direction direction)
{
	const char *in_start, *in_end;
	char *out, *out_start, *out_end, *new_out;
	size_t out_size, out_len;
	bool success = false;
	ConversionResult result;

	*converted = NULL;
	*converted_len = 0;

	in_start = string;
	in_end = in_start + string_len;

	/*
	 * When translating UTF8 to UTF16, these strings are only used
	 * internally, and we obey the given length, so we can simply
	 * use a buffer that is 2x the size.  Add an extra byte to NUL
	 * terminate the results (two bytes for UTF16).
	 */
	if (direction == unicode_builtin_utf8_to_16)
		out_size = (string_len * 2 + 2);
	else
		out_size = (string_len / 2 + 1);

	/* Round to the nearest multiple of 8 */
	out_size = (out_size + 7) & ~7;

	if ((out = malloc(out_size)) == NULL) {
		ntlm_client_set_errmsg(ctx->ntlm, "out of memory");
		return false;
	}

	out_start = out;
	out_end = out_start + out_size;

	/* Make room for NUL termination */
	if (direction == unicode_builtin_utf16_to_8)
		out_end--;

	while (true) {
		if (direction == unicode_builtin_utf8_to_16)
			result = ConvertUTF8toUTF16(
				(const UTF8 **)&in_start, (UTF8 *)in_end,
				(UTF16 **)&out_start, (UTF16 *)out_end, strictConversion);
		else
			result = ConvertUTF16toUTF8(
				(const UTF16 **)&in_start, (UTF16 *)in_end,
				(UTF8 **)&out_start, (UTF8 *)out_end, lenientConversion);

		switch (result) {
			case conversionOK:
				success = true;
				goto done;
			case sourceExhausted:
				ntlm_client_set_errmsg(ctx->ntlm,
					"invalid unicode string; trailing data remains");
				goto done;
			case targetExhausted:
				break;
			case sourceIllegal:
				ntlm_client_set_errmsg(ctx->ntlm,
					"invalid unicode string; trailing data remains");
				goto done;
			default:
				ntlm_client_set_errmsg(ctx->ntlm,
					"unknown unicode conversion failure");
				goto done;
		}

		/* Grow buffer size by 1.5 (rounded up to a multiple of 8) */
		out_size = ((((out_size << 1) - (out_size >> 1)) + 7) & ~7);

		if (out_size > NTLM_UNICODE_MAX_LEN) {
			ntlm_client_set_errmsg(ctx->ntlm,
				"unicode conversion too large");
			goto done;
		}

		if ((new_out = realloc(out, out_size)) == NULL) {
			ntlm_client_set_errmsg(ctx->ntlm, "out of memory");
			goto done;
		}

		out_len = out_start - out;

		out = new_out;
		out_start = new_out + out_len;
		out_end = out + out_size;

		/* Make room for NUL termination */
		out_end -= (direction == unicode_builtin_utf8_to_16) ? 2 : 1;
	}

done:
	if (!success) {
		free(out);
		return false;
	}

	out_len = (out_start - out);

	/* NUL terminate */
	out[out_len] = '\0';

	if (direction == unicode_builtin_utf8_to_16)
		out[out_len+1] = '\0';

	*converted = out;
	*converted_len = out_len;
	return true;
}