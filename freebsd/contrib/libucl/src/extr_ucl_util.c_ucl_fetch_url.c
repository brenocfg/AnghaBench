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
struct url_stat {size_t size; } ;
struct url {int dummy; } ;
typedef  unsigned char const ucl_curl_cbdata ;
typedef  int /*<<< orphan*/  UT_string ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  curl_easy_strerror (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fetchFreeURL (struct url*) ; 
 struct url* fetchParseURL (unsigned char const*) ; 
 int /*<<< orphan*/ * fetchXGet (struct url*,struct url_stat*,char*) ; 
 int fread (unsigned char*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (size_t) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_create_err (int /*<<< orphan*/ **,char*,...) ; 
 unsigned char const* ucl_curl_write_callback ; 

bool
ucl_fetch_url (const unsigned char *url, unsigned char **buf, size_t *buflen,
		UT_string **err, bool must_exist)
{

#ifdef HAVE_FETCH_H
	struct url *fetch_url;
	struct url_stat us;
	FILE *in;

	fetch_url = fetchParseURL (url);
	if (fetch_url == NULL) {
		ucl_create_err (err, "invalid URL %s: %s",
				url, strerror (errno));
		return false;
	}
	if ((in = fetchXGet (fetch_url, &us, "")) == NULL) {
		if (!must_exist) {
			ucl_create_err (err, "cannot fetch URL %s: %s",
				url, strerror (errno));
		}
		fetchFreeURL (fetch_url);
		return false;
	}

	*buflen = us.size;
	*buf = malloc (*buflen);
	if (*buf == NULL) {
		ucl_create_err (err, "cannot allocate buffer for URL %s: %s",
				url, strerror (errno));
		fclose (in);
		fetchFreeURL (fetch_url);
		return false;
	}

	if (fread (*buf, *buflen, 1, in) != 1) {
		ucl_create_err (err, "cannot read URL %s: %s",
				url, strerror (errno));
		fclose (in);
		fetchFreeURL (fetch_url);
		return false;
	}

	fetchFreeURL (fetch_url);
	return true;
#elif defined(CURL_FOUND)
	CURL *curl;
	int r;
	struct ucl_curl_cbdata cbdata;

	curl = curl_easy_init ();
	if (curl == NULL) {
		ucl_create_err (err, "CURL interface is broken");
		return false;
	}
	if ((r = curl_easy_setopt (curl, CURLOPT_URL, url)) != CURLE_OK) {
		ucl_create_err (err, "invalid URL %s: %s",
				url, curl_easy_strerror (r));
		curl_easy_cleanup (curl);
		return false;
	}
	curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, ucl_curl_write_callback);
	cbdata.buf = NULL;
	cbdata.buflen = 0;
	curl_easy_setopt (curl, CURLOPT_WRITEDATA, &cbdata);

	if ((r = curl_easy_perform (curl)) != CURLE_OK) {
		if (!must_exist) {
			ucl_create_err (err, "error fetching URL %s: %s",
				url, curl_easy_strerror (r));
		}
		curl_easy_cleanup (curl);
		if (cbdata.buf) {
			free (cbdata.buf);
		}
		return false;
	}
	*buf = cbdata.buf;
	*buflen = cbdata.buflen;

	return true;
#else
	ucl_create_err (err, "URL support is disabled");
	return false;
#endif
}