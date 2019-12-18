#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timeout_header ;
struct xml_ctx {char* name; struct remote_lock* userData; int /*<<< orphan*/  userFunc; int /*<<< orphan*/ * cdata; scalar_t__ len; } ;
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct slot_results {scalar_t__ curl_result; int http_code; } ;
struct remote_lock {int timeout; char* token; char* owner; char* url; struct remote_lock* next; int /*<<< orphan*/  start_time; } ;
struct curl_slist {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct buffer {struct strbuf buf; int /*<<< orphan*/  member_1; struct strbuf member_0; } ;
struct active_request_slot {int /*<<< orphan*/  curl; struct slot_results* results; } ;
typedef  enum XML_Status { ____Placeholder_XML_Status } XML_Status ;
typedef  int /*<<< orphan*/  XML_Parser ;
struct TYPE_2__ {struct remote_lock* locks; int /*<<< orphan*/  url; } ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_FILE ; 
 int /*<<< orphan*/  CURLOPT_HTTPHEADER ; 
 int /*<<< orphan*/  DAV_LOCK ; 
 int /*<<< orphan*/  DAV_MKCOL ; 
 int /*<<< orphan*/  FREE_AND_NULL (struct remote_lock*) ; 
 int /*<<< orphan*/  LOCK_REQUEST ; 
 struct strbuf STRBUF_INIT ; 
 char* XML_ErrorString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_GetErrorCode (int /*<<< orphan*/ ) ; 
 int XML_Parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XML_ParserCreate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XML_ParserFree (int /*<<< orphan*/ ) ; 
 int XML_STATUS_OK ; 
 int /*<<< orphan*/  XML_SetCharacterDataHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetElementHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetUserData (int /*<<< orphan*/ ,struct xml_ctx*) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  curl_setup_http (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_setup_http_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct strbuf* curl_slist_append (struct strbuf*,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct strbuf*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite_buffer ; 
 struct active_request_slot* get_active_slot () ; 
 int /*<<< orphan*/  handle_new_lock_ctx ; 
 struct strbuf* http_copy_default_headers () ; 
 int /*<<< orphan*/  ident_default_email () ; 
 TYPE_1__* repo ; 
 int /*<<< orphan*/  run_active_slot (struct active_request_slot*) ; 
 scalar_t__ start_active_slot (struct active_request_slot*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (char*,char) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 void* xcalloc (int,int) ; 
 int /*<<< orphan*/  xml_cdata ; 
 int /*<<< orphan*/  xml_end_tag ; 
 char* xml_entities (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xml_start_tag ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,long) ; 
 char* xstrfmt (char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct remote_lock *lock_remote(const char *path, long timeout)
{
	struct active_request_slot *slot;
	struct slot_results results;
	struct buffer out_buffer = { STRBUF_INIT, 0 };
	struct strbuf in_buffer = STRBUF_INIT;
	char *url;
	char *ep;
	char timeout_header[25];
	struct remote_lock *lock = NULL;
	struct curl_slist *dav_headers = http_copy_default_headers();
	struct xml_ctx ctx;
	char *escaped;

	url = xstrfmt("%s%s", repo->url, path);

	/* Make sure leading directories exist for the remote ref */
	ep = strchr(url + strlen(repo->url) + 1, '/');
	while (ep) {
		char saved_character = ep[1];
		ep[1] = '\0';
		slot = get_active_slot();
		slot->results = &results;
		curl_setup_http_get(slot->curl, url, DAV_MKCOL);
		if (start_active_slot(slot)) {
			run_active_slot(slot);
			if (results.curl_result != CURLE_OK &&
			    results.http_code != 405) {
				fprintf(stderr,
					"Unable to create branch path %s\n",
					url);
				free(url);
				return NULL;
			}
		} else {
			fprintf(stderr, "Unable to start MKCOL request\n");
			free(url);
			return NULL;
		}
		ep[1] = saved_character;
		ep = strchr(ep + 1, '/');
	}

	escaped = xml_entities(ident_default_email());
	strbuf_addf(&out_buffer.buf, LOCK_REQUEST, escaped);
	free(escaped);

	xsnprintf(timeout_header, sizeof(timeout_header), "Timeout: Second-%ld", timeout);
	dav_headers = curl_slist_append(dav_headers, timeout_header);
	dav_headers = curl_slist_append(dav_headers, "Content-Type: text/xml");

	slot = get_active_slot();
	slot->results = &results;
	curl_setup_http(slot->curl, url, DAV_LOCK, &out_buffer, fwrite_buffer);
	curl_easy_setopt(slot->curl, CURLOPT_HTTPHEADER, dav_headers);
	curl_easy_setopt(slot->curl, CURLOPT_FILE, &in_buffer);

	lock = xcalloc(1, sizeof(*lock));
	lock->timeout = -1;

	if (start_active_slot(slot)) {
		run_active_slot(slot);
		if (results.curl_result == CURLE_OK) {
			XML_Parser parser = XML_ParserCreate(NULL);
			enum XML_Status result;
			ctx.name = xcalloc(10, 1);
			ctx.len = 0;
			ctx.cdata = NULL;
			ctx.userFunc = handle_new_lock_ctx;
			ctx.userData = lock;
			XML_SetUserData(parser, &ctx);
			XML_SetElementHandler(parser, xml_start_tag,
					      xml_end_tag);
			XML_SetCharacterDataHandler(parser, xml_cdata);
			result = XML_Parse(parser, in_buffer.buf,
					   in_buffer.len, 1);
			free(ctx.name);
			if (result != XML_STATUS_OK) {
				fprintf(stderr, "XML error: %s\n",
					XML_ErrorString(
						XML_GetErrorCode(parser)));
				lock->timeout = -1;
			}
			XML_ParserFree(parser);
		} else {
			fprintf(stderr,
				"error: curl result=%d, HTTP code=%ld\n",
				results.curl_result, results.http_code);
		}
	} else {
		fprintf(stderr, "Unable to start LOCK request\n");
	}

	curl_slist_free_all(dav_headers);
	strbuf_release(&out_buffer.buf);
	strbuf_release(&in_buffer);

	if (lock->token == NULL || lock->timeout <= 0) {
		free(lock->token);
		free(lock->owner);
		free(url);
		FREE_AND_NULL(lock);
	} else {
		lock->url = url;
		lock->start_time = time(NULL);
		lock->next = repo->locks;
		repo->locks = lock;
	}

	return lock;
}