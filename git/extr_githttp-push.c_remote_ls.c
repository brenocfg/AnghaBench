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
struct xml_ctx {char* name; struct remote_ls_ctx* userData; int /*<<< orphan*/  userFunc; int /*<<< orphan*/ * cdata; scalar_t__ len; } ;
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct slot_results {scalar_t__ curl_result; } ;
struct remote_ls_ctx {int flags; char* path; void (* userFunc ) (struct remote_ls_ctx*) ;void* userData; scalar_t__ dentry_flags; int /*<<< orphan*/ * dentry_name; } ;
struct curl_slist {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct buffer {struct strbuf buf; int /*<<< orphan*/  member_1; struct strbuf member_0; } ;
struct active_request_slot {int /*<<< orphan*/  curl; struct slot_results* results; } ;
typedef  enum XML_Status { ____Placeholder_XML_Status } XML_Status ;
typedef  int /*<<< orphan*/  XML_Parser ;
struct TYPE_2__ {int /*<<< orphan*/  url; } ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_FILE ; 
 int /*<<< orphan*/  CURLOPT_HTTPHEADER ; 
 int /*<<< orphan*/  DAV_PROPFIND ; 
 int /*<<< orphan*/  PROPFIND_ALL_REQUEST ; 
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
 struct strbuf* curl_slist_append (struct strbuf*,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct strbuf*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite_buffer ; 
 struct active_request_slot* get_active_slot () ; 
 int /*<<< orphan*/  handle_remote_ls_ctx ; 
 struct strbuf* http_copy_default_headers () ; 
 TYPE_1__* repo ; 
 int /*<<< orphan*/  run_active_slot (struct active_request_slot*) ; 
 scalar_t__ start_active_slot (struct active_request_slot*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* xcalloc (int,int) ; 
 int /*<<< orphan*/  xml_cdata ; 
 int /*<<< orphan*/  xml_end_tag ; 
 int /*<<< orphan*/  xml_start_tag ; 
 char* xstrdup (char const*) ; 
 char* xstrfmt (char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void remote_ls(const char *path, int flags,
		      void (*userFunc)(struct remote_ls_ctx *ls),
		      void *userData)
{
	char *url = xstrfmt("%s%s", repo->url, path);
	struct active_request_slot *slot;
	struct slot_results results;
	struct strbuf in_buffer = STRBUF_INIT;
	struct buffer out_buffer = { STRBUF_INIT, 0 };
	struct curl_slist *dav_headers = http_copy_default_headers();
	struct xml_ctx ctx;
	struct remote_ls_ctx ls;

	ls.flags = flags;
	ls.path = xstrdup(path);
	ls.dentry_name = NULL;
	ls.dentry_flags = 0;
	ls.userData = userData;
	ls.userFunc = userFunc;

	strbuf_addstr(&out_buffer.buf, PROPFIND_ALL_REQUEST);

	dav_headers = curl_slist_append(dav_headers, "Depth: 1");
	dav_headers = curl_slist_append(dav_headers, "Content-Type: text/xml");

	slot = get_active_slot();
	slot->results = &results;
	curl_setup_http(slot->curl, url, DAV_PROPFIND,
			&out_buffer, fwrite_buffer);
	curl_easy_setopt(slot->curl, CURLOPT_HTTPHEADER, dav_headers);
	curl_easy_setopt(slot->curl, CURLOPT_FILE, &in_buffer);

	if (start_active_slot(slot)) {
		run_active_slot(slot);
		if (results.curl_result == CURLE_OK) {
			XML_Parser parser = XML_ParserCreate(NULL);
			enum XML_Status result;
			ctx.name = xcalloc(10, 1);
			ctx.len = 0;
			ctx.cdata = NULL;
			ctx.userFunc = handle_remote_ls_ctx;
			ctx.userData = &ls;
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
			}
			XML_ParserFree(parser);
		}
	} else {
		fprintf(stderr, "Unable to start PROPFIND request\n");
	}

	free(ls.path);
	free(url);
	strbuf_release(&out_buffer.buf);
	strbuf_release(&in_buffer);
	curl_slist_free_all(dav_headers);
}