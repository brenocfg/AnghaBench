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
typedef  int /*<<< orphan*/  git_pkt ;

/* Variables and functions */
 int GIT_EBUFS ; 
 int GIT_ERROR ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 char const GIT_SIDE_BAND_DATA ; 
 char const GIT_SIDE_BAND_ERROR ; 
 char const GIT_SIDE_BAND_PROGRESS ; 
 size_t PKT_LEN_SIZE ; 
 int ack_pkt (int /*<<< orphan*/ **,char const*,size_t) ; 
 int comment_pkt (int /*<<< orphan*/ **,char const*,size_t) ; 
 int data_pkt (int /*<<< orphan*/ **,char const*,size_t) ; 
 int err_pkt (int /*<<< orphan*/ **,char const*,size_t) ; 
 int flush_pkt (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git__prefixncmp (char const*,size_t,char*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_error_set_str (int /*<<< orphan*/ ,char*) ; 
 int nak_pkt (int /*<<< orphan*/ **) ; 
 int ng_pkt (int /*<<< orphan*/ **,char const*,size_t) ; 
 int ok_pkt (int /*<<< orphan*/ **,char const*,size_t) ; 
 int parse_len (size_t*,char const*,size_t) ; 
 int ref_pkt (int /*<<< orphan*/ **,char const*,size_t) ; 
 int sideband_error_pkt (int /*<<< orphan*/ **,char const*,size_t) ; 
 int sideband_progress_pkt (int /*<<< orphan*/ **,char const*,size_t) ; 
 int unpack_pkt (int /*<<< orphan*/ **,char const*,size_t) ; 

int git_pkt_parse_line(
	git_pkt **pkt, const char **endptr, const char *line, size_t linelen)
{
	int error;
	size_t len;

	if ((error = parse_len(&len, line, linelen)) < 0) {
		/*
		 * If we fail to parse the length, it might be
		 * because the server is trying to send us the
		 * packfile already or because we do not yet have
		 * enough data.
		 */
		if (error == GIT_EBUFS)
			;
		else if (!git__prefixncmp(line, linelen, "PACK"))
			git_error_set(GIT_ERROR_NET, "unexpected pack file");
		else
			git_error_set(GIT_ERROR_NET, "bad packet length");
		return error;
	}

	/*
	 * Make sure there is enough in the buffer to satisfy
	 * this line.
	 */
	if (linelen < len)
		return GIT_EBUFS;

	/*
	 * The length has to be exactly 0 in case of a flush
	 * packet or greater than PKT_LEN_SIZE, as the decoded
	 * length includes its own encoded length of four bytes.
	 */
	if (len != 0 && len < PKT_LEN_SIZE)
		return GIT_ERROR;

	line += PKT_LEN_SIZE;
	/*
	 * The Git protocol does not specify empty lines as part
	 * of the protocol. Not knowing what to do with an empty
	 * line, we should return an error upon hitting one.
	 */
	if (len == PKT_LEN_SIZE) {
		git_error_set_str(GIT_ERROR_NET, "Invalid empty packet");
		return GIT_ERROR;
	}

	if (len == 0) { /* Flush pkt */
		*endptr = line;
		return flush_pkt(pkt);
	}

	len -= PKT_LEN_SIZE; /* the encoded length includes its own size */

	if (*line == GIT_SIDE_BAND_DATA)
		error = data_pkt(pkt, line, len);
	else if (*line == GIT_SIDE_BAND_PROGRESS)
		error = sideband_progress_pkt(pkt, line, len);
	else if (*line == GIT_SIDE_BAND_ERROR)
		error = sideband_error_pkt(pkt, line, len);
	else if (!git__prefixncmp(line, len, "ACK"))
		error = ack_pkt(pkt, line, len);
	else if (!git__prefixncmp(line, len, "NAK"))
		error = nak_pkt(pkt);
	else if (!git__prefixncmp(line, len, "ERR"))
		error = err_pkt(pkt, line, len);
	else if (*line == '#')
		error = comment_pkt(pkt, line, len);
	else if (!git__prefixncmp(line, len, "ok"))
		error = ok_pkt(pkt, line, len);
	else if (!git__prefixncmp(line, len, "ng"))
		error = ng_pkt(pkt, line, len);
	else if (!git__prefixncmp(line, len, "unpack"))
		error = unpack_pkt(pkt, line, len);
	else
		error = ref_pkt(pkt, line, len);

	*endptr = line + len;

	return error;
}