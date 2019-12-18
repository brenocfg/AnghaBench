#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {scalar_t__ avail_in; int avail_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * next_in; } ;
typedef  TYPE_1__ lzma_stream ;
typedef  int lzma_ret ;
typedef  scalar_t__ lzma_action ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
#define  LZMA_BUF_ERROR 132 
 int /*<<< orphan*/  LZMA_CONCATENATED ; 
#define  LZMA_DATA_ERROR 131 
 scalar_t__ LZMA_FINISH ; 
#define  LZMA_FORMAT_ERROR 130 
#define  LZMA_MEM_ERROR 129 
 int LZMA_OK ; 
#define  LZMA_OPTIONS_ERROR 128 
 scalar_t__ LZMA_RUN ; 
 int LZMA_STREAM_END ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 size_t const fwrite (int /*<<< orphan*/ *,int,size_t const,int /*<<< orphan*/ ) ; 
 int lzma_alone_decoder (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int lzma_code (TYPE_1__*,scalar_t__) ; 
 int lzma_stream_decoder (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_errorf (char*,char const*,...) ; 
 int /*<<< orphan*/  stdout ; 
 char const* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uncompress(lzma_stream *strm, FILE *file, const char *filename)
{
	lzma_ret ret;

	// Initialize the decoder
#ifdef LZMADEC
	ret = lzma_alone_decoder(strm, UINT64_MAX);
#else
	ret = lzma_stream_decoder(strm, UINT64_MAX, LZMA_CONCATENATED);
#endif

	// The only reasonable error here is LZMA_MEM_ERROR.
	if (ret != LZMA_OK) {
		my_errorf("%s", ret == LZMA_MEM_ERROR ? strerror(ENOMEM)
				: "Internal error (bug)");
		exit(EXIT_FAILURE);
	}

	// Input and output buffers
	uint8_t in_buf[BUFSIZ];
	uint8_t out_buf[BUFSIZ];

	strm->avail_in = 0;
	strm->next_out = out_buf;
	strm->avail_out = BUFSIZ;

	lzma_action action = LZMA_RUN;

	while (true) {
		if (strm->avail_in == 0) {
			strm->next_in = in_buf;
			strm->avail_in = fread(in_buf, 1, BUFSIZ, file);

			if (ferror(file)) {
				// POSIX says that fread() sets errno if
				// an error occurred. ferror() doesn't
				// touch errno.
				my_errorf("%s: Error reading input file: %s",
						filename, strerror(errno));
				exit(EXIT_FAILURE);
			}

#ifndef LZMADEC
			// When using LZMA_CONCATENATED, we need to tell
			// liblzma when it has got all the input.
			if (feof(file))
				action = LZMA_FINISH;
#endif
		}

		ret = lzma_code(strm, action);

		// Write and check write error before checking decoder error.
		// This way as much data as possible gets written to output
		// even if decoder detected an error.
		if (strm->avail_out == 0 || ret != LZMA_OK) {
			const size_t write_size = BUFSIZ - strm->avail_out;

			if (fwrite(out_buf, 1, write_size, stdout)
					!= write_size) {
				// Wouldn't be a surprise if writing to stderr
				// would fail too but at least try to show an
				// error message.
				my_errorf("Cannot write to standard output: "
						"%s", strerror(errno));
				exit(EXIT_FAILURE);
			}

			strm->next_out = out_buf;
			strm->avail_out = BUFSIZ;
		}

		if (ret != LZMA_OK) {
			if (ret == LZMA_STREAM_END) {
#ifdef LZMADEC
				// Check that there's no trailing garbage.
				if (strm->avail_in != 0
						|| fread(in_buf, 1, 1, file)
							!= 0
						|| !feof(file))
					ret = LZMA_DATA_ERROR;
				else
					return;
#else
				// lzma_stream_decoder() already guarantees
				// that there's no trailing garbage.
				assert(strm->avail_in == 0);
				assert(action == LZMA_FINISH);
				assert(feof(file));
				return;
#endif
			}

			const char *msg;
			switch (ret) {
			case LZMA_MEM_ERROR:
				msg = strerror(ENOMEM);
				break;

			case LZMA_FORMAT_ERROR:
				msg = "File format not recognized";
				break;

			case LZMA_OPTIONS_ERROR:
				// FIXME: Better message?
				msg = "Unsupported compression options";
				break;

			case LZMA_DATA_ERROR:
				msg = "File is corrupt";
				break;

			case LZMA_BUF_ERROR:
				msg = "Unexpected end of input";
				break;

			default:
				msg = "Internal error (bug)";
				break;
			}

			my_errorf("%s: %s", filename, msg);
			exit(EXIT_FAILURE);
		}
	}
}