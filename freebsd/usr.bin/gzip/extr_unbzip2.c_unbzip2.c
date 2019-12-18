#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
struct TYPE_5__ {size_t avail_in; char* next_in; char* next_out; scalar_t__ avail_out; int /*<<< orphan*/ * opaque; int /*<<< orphan*/ * bzfree; int /*<<< orphan*/ * bzalloc; } ;
typedef  TYPE_1__ bz_stream ;

/* Variables and functions */
 scalar_t__ BUFLEN ; 
 int BZ2_bzDecompress (TYPE_1__*) ; 
 int BZ2_bzDecompressEnd (TYPE_1__*) ; 
 int const BZ2_bzDecompressInit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  BZ_DATA_ERROR 132 
#define  BZ_DATA_ERROR_MAGIC 131 
#define  BZ_MEM_ERROR 130 
#define  BZ_OK 129 
#define  BZ_STREAM_END 128 
 int /*<<< orphan*/  check_siginfo () ; 
 int /*<<< orphan*/  infile_newdata (scalar_t__) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  maybe_err (char*) ; 
 int /*<<< orphan*/  maybe_errx (char*) ; 
 int /*<<< orphan*/  maybe_warnx (char*,...) ; 
 scalar_t__ read (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  tflag ; 
 scalar_t__ write (int,char*,scalar_t__) ; 

__attribute__((used)) static off_t
unbzip2(int in, int out, char *pre, size_t prelen, off_t *bytes_in)
{
	int		ret, end_of_file, cold = 0;
	off_t		bytes_out = 0;
	bz_stream	bzs;
	static char	*inbuf, *outbuf;

	if (inbuf == NULL)
		inbuf = malloc(BUFLEN);
	if (outbuf == NULL)
		outbuf = malloc(BUFLEN);
	if (inbuf == NULL || outbuf == NULL)
	        maybe_err("malloc");

	bzs.bzalloc = NULL;
	bzs.bzfree = NULL;
	bzs.opaque = NULL;

	end_of_file = 0;
	ret = BZ2_bzDecompressInit(&bzs, 0, 0);
	if (ret != BZ_OK)
	        maybe_errx("bzip2 init");

	/* Prepend. */
	bzs.avail_in = prelen;
	bzs.next_in = pre;

	if (bytes_in)
		*bytes_in = prelen;

	while (ret == BZ_OK) {
		check_siginfo();
	        if (bzs.avail_in == 0 && !end_of_file) {
			ssize_t	n;

	                n = read(in, inbuf, BUFLEN);
	                if (n < 0)
	                        maybe_err("read");
	                if (n == 0)
	                        end_of_file = 1;
			infile_newdata(n);
	                bzs.next_in = inbuf;
	                bzs.avail_in = n;
			if (bytes_in)
				*bytes_in += n;
	        }

	        bzs.next_out = outbuf;
	        bzs.avail_out = BUFLEN;
	        ret = BZ2_bzDecompress(&bzs);

	        switch (ret) {
	        case BZ_STREAM_END:
	        case BZ_OK:
	                if (ret == BZ_OK && end_of_file) {
				/*
				 * If we hit this after a stream end, consider
				 * it as the end of the whole file and don't
				 * bail out.
				 */
				if (cold == 1)
					ret = BZ_STREAM_END;
				else
					maybe_errx("truncated file");
			}
			cold = 0;
	                if (!tflag && bzs.avail_out != BUFLEN) {
				ssize_t	n;

	                        n = write(out, outbuf, BUFLEN - bzs.avail_out);
	                        if (n < 0)
	                                maybe_err("write");
	                	bytes_out += n;
	                }
			if (ret == BZ_STREAM_END && !end_of_file) {
				if (BZ2_bzDecompressEnd(&bzs) != BZ_OK ||
				    BZ2_bzDecompressInit(&bzs, 0, 0) != BZ_OK)
					maybe_errx("bzip2 re-init");
				cold = 1;
				ret = BZ_OK;
			}
			break;

	        case BZ_DATA_ERROR:
	                maybe_warnx("bzip2 data integrity error");
			break;

	        case BZ_DATA_ERROR_MAGIC:
	                maybe_warnx("bzip2 magic number error");
			break;

	        case BZ_MEM_ERROR:
	                maybe_warnx("bzip2 out of memory");
			break;
		
		default:	
			maybe_warnx("unknown bzip2 error: %d", ret);
			break;
	        }
	}

	if (ret != BZ_STREAM_END || BZ2_bzDecompressEnd(&bzs) != BZ_OK)
	        return (-1);

	return (bytes_out);
}