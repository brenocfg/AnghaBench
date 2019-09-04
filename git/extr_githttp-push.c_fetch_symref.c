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
struct strbuf {scalar_t__ len; char const* buf; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  url; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (char*) ; 
 scalar_t__ HTTP_OK ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  curl_errorstr ; 
 int /*<<< orphan*/  die (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_oid_hex (char const*,struct object_id*) ; 
 scalar_t__ http_get_strbuf (char*,struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidclr (struct object_id*) ; 
 TYPE_1__* repo ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 char* xmemdupz (char const*,int) ; 
 char* xstrfmt (char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void fetch_symref(const char *path, char **symref, struct object_id *oid)
{
	char *url = xstrfmt("%s%s", repo->url, path);
	struct strbuf buffer = STRBUF_INIT;
	const char *name;

	if (http_get_strbuf(url, &buffer, NULL) != HTTP_OK)
		die("Couldn't get %s for remote symref\n%s", url,
		    curl_errorstr);
	free(url);

	FREE_AND_NULL(*symref);
	oidclr(oid);

	if (buffer.len == 0)
		return;

	/* Cut off trailing newline. */
	strbuf_rtrim(&buffer);

	/* If it's a symref, set the refname; otherwise try for a sha1 */
	if (skip_prefix(buffer.buf, "ref: ", &name)) {
		*symref = xmemdupz(name, buffer.len - (name - buffer.buf));
	} else {
		get_oid_hex(buffer.buf, oid);
	}

	strbuf_release(&buffer);
}