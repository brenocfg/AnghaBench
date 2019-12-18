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
typedef  int lzma_ret ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
#define  LZMA_BUF_ERROR 139 
#define  LZMA_DATA_ERROR 138 
#define  LZMA_FORMAT_ERROR 137 
#define  LZMA_GET_CHECK 136 
#define  LZMA_MEMLIMIT_ERROR 135 
#define  LZMA_MEM_ERROR 134 
#define  LZMA_NO_CHECK 133 
#define  LZMA_OK 132 
#define  LZMA_OPTIONS_ERROR 131 
#define  LZMA_PROG_ERROR 130 
#define  LZMA_STREAM_END 129 
#define  LZMA_UNSUPPORTED_CHECK 128 
 char const* _ (char*) ; 
 char const* strerror (int /*<<< orphan*/ ) ; 

extern const char *
message_strm(lzma_ret code)
{
	switch (code) {
	case LZMA_NO_CHECK:
		return _("No integrity check; not verifying file integrity");

	case LZMA_UNSUPPORTED_CHECK:
		return _("Unsupported type of integrity check; "
				"not verifying file integrity");

	case LZMA_MEM_ERROR:
		return strerror(ENOMEM);

	case LZMA_MEMLIMIT_ERROR:
		return _("Memory usage limit reached");

	case LZMA_FORMAT_ERROR:
		return _("File format not recognized");

	case LZMA_OPTIONS_ERROR:
		return _("Unsupported options");

	case LZMA_DATA_ERROR:
		return _("Compressed data is corrupt");

	case LZMA_BUF_ERROR:
		return _("Unexpected end of input");

	case LZMA_OK:
	case LZMA_STREAM_END:
	case LZMA_GET_CHECK:
	case LZMA_PROG_ERROR:
		// Without "default", compiler will warn if new constants
		// are added to lzma_ret, it is not too easy to forget to
		// add the new constants to this function.
		break;
	}

	return _("Internal error (bug)");
}