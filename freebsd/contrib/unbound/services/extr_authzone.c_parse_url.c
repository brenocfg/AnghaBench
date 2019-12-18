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

/* Variables and functions */
 int AUTH_HTTPS_PORT ; 
 int AUTH_HTTP_PORT ; 
 char* dup_all (char*) ; 
 char* dup_prefix (char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 char* str_find_first_of_chars (char*,char,char) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strstr (char*,char*) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static int
parse_url(char* url, char** host, char** file, int* port, int* ssl)
{
	char* p = url;
	/* parse http://www.example.com/file.htm
	 * or http://127.0.0.1   (index.html)
	 * or https://[::1@1234]/a/b/c/d */
	*ssl = 1;
	*port = AUTH_HTTPS_PORT;

	/* parse http:// or https:// */
	if(strncmp(p, "http://", 7) == 0) {
		p += 7;
		*ssl = 0;
		*port = AUTH_HTTP_PORT;
	} else if(strncmp(p, "https://", 8) == 0) {
		p += 8;
	} else if(strstr(p, "://") && strchr(p, '/') > strstr(p, "://") &&
		strchr(p, ':') >= strstr(p, "://")) {
		char* uri = dup_prefix(p, (size_t)(strstr(p, "://")-p));
		log_err("protocol %s:// not supported (for url %s)",
			uri?uri:"", p);
		free(uri);
		return 0;
	}

	/* parse hostname part */
	if(p[0] == '[') {
		char* end = strchr(p, ']');
		p++; /* skip over [ */
		if(end) {
			*host = dup_prefix(p, (size_t)(end-p));
			if(!*host) return 0;
			p = end+1; /* skip over ] */
		} else {
			*host = dup_all(p);
			if(!*host) return 0;
			p = end;
		}
	} else {
		char* end = str_find_first_of_chars(p, ':', '/');
		if(end) {
			*host = dup_prefix(p, (size_t)(end-p));
			if(!*host) return 0;
		} else {
			*host = dup_all(p);
			if(!*host) return 0;
		}
		p = end; /* at next : or / or NULL */
	}

	/* parse port number */
	if(p && p[0] == ':') {
		char* end = NULL;
		*port = strtol(p+1, &end, 10);
		p = end;
	}

	/* parse filename part */
	while(p && *p == '/')
		p++;
	if(!p || p[0] == 0)
		*file = strdup("index.html");
	else	*file = strdup(p);
	if(!*file) {
		log_err("malloc failure");
		return 0;
	}
	return 1;
}