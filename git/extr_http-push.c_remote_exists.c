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
struct TYPE_2__ {int /*<<< orphan*/  url; } ;

/* Variables and functions */
#define  HTTP_ERROR 130 
#define  HTTP_MISSING_TARGET 129 
#define  HTTP_OK 128 
 char* curl_errorstr ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int http_get_strbuf (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* repo ; 
 char* xstrfmt (char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int remote_exists(const char *path)
{
	char *url = xstrfmt("%s%s", repo->url, path);
	int ret;


	switch (http_get_strbuf(url, NULL, NULL)) {
	case HTTP_OK:
		ret = 1;
		break;
	case HTTP_MISSING_TARGET:
		ret = 0;
		break;
	case HTTP_ERROR:
		error("unable to access '%s': %s", url, curl_errorstr);
		/* fallthrough */
	default:
		ret = -1;
	}
	free(url);
	return ret;
}