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
struct httpread {scalar_t__ content_length; scalar_t__ max_bytes; int got_content_length; int chunked; scalar_t__ in_chunk_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ atol (char*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 scalar_t__ isgraph (char) ; 
 scalar_t__ word_eq (char*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int httpread_hdr_option_analyze(
	struct httpread *h,
	char *hbp       /* pointer to current line in header buffer */
	)
{
	if (word_eq(hbp, "CONTENT-LENGTH:")) {
		while (isgraph(*hbp))
			hbp++;
		while (*hbp == ' ' || *hbp == '\t')
			hbp++;
		if (!isdigit(*hbp))
			return -1;
		h->content_length = atol(hbp);
		if (h->content_length < 0 || h->content_length > h->max_bytes) {
			wpa_printf(MSG_DEBUG,
				   "httpread: Unacceptable Content-Length %d",
				   h->content_length);
			return -1;
		}
		h->got_content_length = 1;
		return 0;
	}
	if (word_eq(hbp, "TRANSFER_ENCODING:") ||
	    word_eq(hbp, "TRANSFER-ENCODING:")) {
		while (isgraph(*hbp))
			hbp++;
		while (*hbp == ' ' || *hbp == '\t')
			hbp++;
		/* There should (?) be no encodings of interest
		 * other than chunked...
		 */
		if (word_eq(hbp, "CHUNKED")) {
			h->chunked = 1;
			h->in_chunk_data = 0;
			/* ignore possible ;<parameters> */
		}
		return 0;
	}
	/* skip anything we don't know, which is a lot */
	return 0;
}