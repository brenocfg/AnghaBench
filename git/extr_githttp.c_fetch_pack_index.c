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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (char*) ; 
 scalar_t__ HTTP_OK ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  end_url_with_slash (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* hash_to_hex (unsigned char*) ; 
 scalar_t__ http_get_file (char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ http_is_verbose ; 
 char* sha1_pack_index_name (unsigned char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *fetch_pack_index(unsigned char *hash, const char *base_url)
{
	char *url, *tmp;
	struct strbuf buf = STRBUF_INIT;

	if (http_is_verbose)
		fprintf(stderr, "Getting index for pack %s\n", hash_to_hex(hash));

	end_url_with_slash(&buf, base_url);
	strbuf_addf(&buf, "objects/pack/pack-%s.idx", hash_to_hex(hash));
	url = strbuf_detach(&buf, NULL);

	strbuf_addf(&buf, "%s.temp", sha1_pack_index_name(hash));
	tmp = strbuf_detach(&buf, NULL);

	if (http_get_file(url, tmp, NULL) != HTTP_OK) {
		error("Unable to get pack index %s", url);
		FREE_AND_NULL(tmp);
	}

	free(url);
	return tmp;
}