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
 int /*<<< orphan*/  end_headers (struct strbuf*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_write (int,char*,char const*,char const*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  hdr_nocache (struct strbuf*) ; 
 int /*<<< orphan*/  http_status (struct strbuf*,int,char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void check_content_type(struct strbuf *hdr, const char *accepted_type)
{
	const char *actual_type = getenv("CONTENT_TYPE");

	if (!actual_type)
		actual_type = "";

	if (strcmp(actual_type, accepted_type)) {
		http_status(hdr, 415, "Unsupported Media Type");
		hdr_nocache(hdr);
		end_headers(hdr);
		format_write(1,
			"Expected POST with Content-Type '%s',"
			" but received '%s' instead.\n",
			accepted_type, actual_type);
		exit(0);
	}
}