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
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  end_url_with_slash (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 

void str_end_url_with_slash(const char *url, char **dest)
{
	struct strbuf buf = STRBUF_INIT;
	end_url_with_slash(&buf, url);
	free(*dest);
	*dest = strbuf_detach(&buf, NULL);
}