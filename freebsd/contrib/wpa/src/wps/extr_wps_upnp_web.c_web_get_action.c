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
struct http_request {int dummy; } ;

/* Variables and functions */
 char* http_request_get_hdr_line (struct http_request*,char*) ; 
 scalar_t__ isgraph (char) ; 
 int os_strlen (char*) ; 
 scalar_t__ os_strncasecmp (char*,char const*,int) ; 
 char* urn_wfawlanconfig ; 

__attribute__((used)) static const char * web_get_action(struct http_request *req,
				   size_t *action_len)
{
	const char *match;
	int match_len;
	char *b;
	char *action;

	*action_len = 0;
	/* The SOAPAction line of the header tells us what we want to do */
	b = http_request_get_hdr_line(req, "SOAPAction:");
	if (b == NULL)
		return NULL;
	if (*b == '"')
		b++;
	else
		return NULL;
	match = urn_wfawlanconfig;
	match_len = os_strlen(urn_wfawlanconfig) - 1;
	if (os_strncasecmp(b, match, match_len))
		return NULL;
	b += match_len;
	/* skip over version */
	while (isgraph(*b) && *b != '#')
		b++;
	if (*b != '#')
		return NULL;
	b++;
	/* Following the sharp(#) should be the action and a double quote */
	action = b;
	while (isgraph(*b) && *b != '"')
		b++;
	if (*b != '"')
		return NULL;
	*action_len = b - action;
	return action;
}