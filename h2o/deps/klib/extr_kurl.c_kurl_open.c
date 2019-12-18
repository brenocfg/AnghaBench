#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {scalar_t__ url; scalar_t__ date; scalar_t__ auth; } ;
typedef  TYPE_1__ s3aux_t ;
struct TYPE_11__ {int fd; long hdr; int m_buf; int /*<<< orphan*/ * buf; int /*<<< orphan*/  curl; int /*<<< orphan*/  multi; } ;
typedef  TYPE_2__ kurl_t ;
struct TYPE_12__ {char* s3keyid; char* s3secretkey; char* s3key_fn; } ;
typedef  TYPE_3__ kurl_opt_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_FOLLOWLOCATION ; 
 int /*<<< orphan*/  CURLOPT_HTTPHEADER ; 
 int /*<<< orphan*/  CURLOPT_NOSIGNAL ; 
 int /*<<< orphan*/  CURLOPT_SSL_VERIFYHOST ; 
 int /*<<< orphan*/  CURLOPT_SSL_VERIFYPEER ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int CURL_MAX_WRITE_SIZE ; 
 int KU_DEF_BUFLEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  curl_multi_init () ; 
 void* curl_slist_append (long,scalar_t__) ; 
 scalar_t__ fill_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  isalnum (char const) ; 
 int /*<<< orphan*/  kurl_close (TYPE_2__*) ; 
 scalar_t__ kurl_isfile (TYPE_2__*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ prepare (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char const* strstr (char const*,char*) ; 
 long write_cb ; 

kurl_t *kurl_open(const char *url, kurl_opt_t *opt)
{
	extern s3aux_t s3_parse(const char *url, const char *_id, const char *_secret, const char *fn);
	const char *p, *q;
	kurl_t *ku;
	int fd = -1, is_file = 1, failed = 0;

	p = strstr(url, "://");
	if (p && *p) {
		for (q = url; q != p; ++q)
			if (!isalnum(*q)) break;
		if (q == p) is_file = 0;
	}
	if (is_file && (fd = open(url, O_RDONLY)) < 0) return 0;

	ku = (kurl_t*)calloc(1, sizeof(kurl_t));
	ku->fd = is_file? fd : -1;
	if (!kurl_isfile(ku)) {
		ku->multi = curl_multi_init();
		ku->curl  = curl_easy_init();
		if (strstr(url, "s3://") == url) {
			s3aux_t a;
			a = s3_parse(url, (opt? opt->s3keyid : 0), (opt? opt->s3secretkey : 0), (opt? opt->s3key_fn : 0));
			if (a.url == 0 || a.date == 0 || a.auth == 0) {
				kurl_close(ku);
				return 0;
			}
			ku->hdr = curl_slist_append(ku->hdr, a.date);
			ku->hdr = curl_slist_append(ku->hdr, a.auth);
			curl_easy_setopt(ku->curl, CURLOPT_URL, a.url);
			curl_easy_setopt(ku->curl, CURLOPT_HTTPHEADER, ku->hdr);
			free(a.date); free(a.auth); free(a.url);
		} else curl_easy_setopt(ku->curl, CURLOPT_URL, url);
		curl_easy_setopt(ku->curl, CURLOPT_WRITEDATA, ku);
		curl_easy_setopt(ku->curl, CURLOPT_VERBOSE, 0L);
		curl_easy_setopt(ku->curl, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt(ku->curl, CURLOPT_WRITEFUNCTION, write_cb);
		curl_easy_setopt(ku->curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(ku->curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(ku->curl, CURLOPT_FOLLOWLOCATION, 1L);
	}
	ku->m_buf = KU_DEF_BUFLEN;
	if (!kurl_isfile(ku) && ku->m_buf < CURL_MAX_WRITE_SIZE * 2)
		ku->m_buf = CURL_MAX_WRITE_SIZE * 2; // for remote files, the buffer set to 2*CURL_MAX_WRITE_SIZE
	ku->buf = (uint8_t*)calloc(ku->m_buf, 1);
	if (kurl_isfile(ku)) failed = (fill_buffer(ku) <= 0);
	else failed = (prepare(ku, 0) < 0 || fill_buffer(ku) <= 0);
	if (failed) {
		kurl_close(ku);
		return 0;
	}
	return ku;
}