#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ lzma_ret ;
struct TYPE_17__ {int /*<<< orphan*/  src_name; } ;
typedef  TYPE_1__ file_pair ;
typedef  enum format_type { ____Placeholder_format_type } format_type ;
typedef  enum coder_init_ret { ____Placeholder_coder_init_ret } coder_init_ret ;
struct TYPE_19__ {int /*<<< orphan*/  options; } ;
struct TYPE_18__ {scalar_t__ avail_out; int /*<<< orphan*/ * next_out; } ;

/* Variables and functions */
 int CODER_INIT_ERROR ; 
 int CODER_INIT_NORMAL ; 
 int CODER_INIT_PASSTHRU ; 
#define  FORMAT_AUTO 131 
#define  FORMAT_LZMA 130 
#define  FORMAT_RAW 129 
#define  FORMAT_XZ 128 
 int /*<<< orphan*/  LZMA_CONCATENATED ; 
 scalar_t__ LZMA_FORMAT_ERROR ; 
 int /*<<< orphan*/  LZMA_IGNORE_CHECK ; 
 scalar_t__ LZMA_MEMLIMIT_ERROR ; 
 scalar_t__ LZMA_OK ; 
 scalar_t__ LZMA_PROG_ERROR ; 
 int /*<<< orphan*/  LZMA_RUN ; 
 int /*<<< orphan*/  LZMA_TELL_UNSUPPORTED_CHECK ; 
 scalar_t__ MODE_COMPRESS ; 
 scalar_t__ MODE_DECOMPRESS ; 
 int /*<<< orphan*/  V_ERROR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check ; 
 TYPE_5__* filters ; 
 int /*<<< orphan*/  hardware_memlimit_get (scalar_t__) ; 
 int hardware_threads_get () ; 
 int /*<<< orphan*/  is_format_lzma () ; 
 int /*<<< orphan*/  is_format_xz () ; 
 scalar_t__ lzma_alone_decoder (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lzma_alone_encoder (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lzma_code (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_memusage (TYPE_2__*) ; 
 scalar_t__ lzma_raw_decoder (TYPE_2__*,TYPE_5__*) ; 
 scalar_t__ lzma_raw_encoder (TYPE_2__*,TYPE_5__*) ; 
 scalar_t__ lzma_stream_decoder (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lzma_stream_encoder (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lzma_stream_encoder_mt (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  message_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_mem_needed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_strm (scalar_t__) ; 
 int /*<<< orphan*/  mt_options ; 
 int /*<<< orphan*/  opt_force ; 
 int opt_format ; 
 scalar_t__ opt_ignore_check ; 
 scalar_t__ opt_mode ; 
 int /*<<< orphan*/  opt_single_stream ; 
 int /*<<< orphan*/  opt_stdout ; 
 TYPE_2__ strm ; 

__attribute__((used)) static enum coder_init_ret
coder_init(file_pair *pair)
{
	lzma_ret ret = LZMA_PROG_ERROR;

	if (opt_mode == MODE_COMPRESS) {
#ifdef HAVE_ENCODERS
		switch (opt_format) {
		case FORMAT_AUTO:
			// args.c ensures this.
			assert(0);
			break;

		case FORMAT_XZ:
#	ifdef MYTHREAD_ENABLED
			if (hardware_threads_get() > 1)
				ret = lzma_stream_encoder_mt(
						&strm, &mt_options);
			else
#	endif
				ret = lzma_stream_encoder(
						&strm, filters, check);
			break;

		case FORMAT_LZMA:
			ret = lzma_alone_encoder(&strm, filters[0].options);
			break;

		case FORMAT_RAW:
			ret = lzma_raw_encoder(&strm, filters);
			break;
		}
#endif
	} else {
#ifdef HAVE_DECODERS
		uint32_t flags = 0;

		// It seems silly to warn about unsupported check if the
		// check won't be verified anyway due to --ignore-check.
		if (opt_ignore_check)
			flags |= LZMA_IGNORE_CHECK;
		else
			flags |= LZMA_TELL_UNSUPPORTED_CHECK;

		if (!opt_single_stream)
			flags |= LZMA_CONCATENATED;

		// We abuse FORMAT_AUTO to indicate unknown file format,
		// for which we may consider passthru mode.
		enum format_type init_format = FORMAT_AUTO;

		switch (opt_format) {
		case FORMAT_AUTO:
			if (is_format_xz())
				init_format = FORMAT_XZ;
			else if (is_format_lzma())
				init_format = FORMAT_LZMA;
			break;

		case FORMAT_XZ:
			if (is_format_xz())
				init_format = FORMAT_XZ;
			break;

		case FORMAT_LZMA:
			if (is_format_lzma())
				init_format = FORMAT_LZMA;
			break;

		case FORMAT_RAW:
			init_format = FORMAT_RAW;
			break;
		}

		switch (init_format) {
		case FORMAT_AUTO:
			// Unknown file format. If --decompress --stdout
			// --force have been given, then we copy the input
			// as is to stdout. Checking for MODE_DECOMPRESS
			// is needed, because we don't want to do use
			// passthru mode with --test.
			if (opt_mode == MODE_DECOMPRESS
					&& opt_stdout && opt_force)
				return CODER_INIT_PASSTHRU;

			ret = LZMA_FORMAT_ERROR;
			break;

		case FORMAT_XZ:
			ret = lzma_stream_decoder(&strm,
					hardware_memlimit_get(
						MODE_DECOMPRESS), flags);
			break;

		case FORMAT_LZMA:
			ret = lzma_alone_decoder(&strm,
					hardware_memlimit_get(
						MODE_DECOMPRESS));
			break;

		case FORMAT_RAW:
			// Memory usage has already been checked in
			// coder_set_compression_settings().
			ret = lzma_raw_decoder(&strm, filters);
			break;
		}

		// Try to decode the headers. This will catch too low
		// memory usage limit in case it happens in the first
		// Block of the first Stream, which is where it very
		// probably will happen if it is going to happen.
		if (ret == LZMA_OK && init_format != FORMAT_RAW) {
			strm.next_out = NULL;
			strm.avail_out = 0;
			ret = lzma_code(&strm, LZMA_RUN);
		}
#endif
	}

	if (ret != LZMA_OK) {
		message_error("%s: %s", pair->src_name, message_strm(ret));
		if (ret == LZMA_MEMLIMIT_ERROR)
			message_mem_needed(V_ERROR, lzma_memusage(&strm));

		return CODER_INIT_ERROR;
	}

	return CODER_INIT_NORMAL;
}