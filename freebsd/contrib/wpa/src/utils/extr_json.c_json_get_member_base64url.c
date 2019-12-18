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
struct wpabuf {int dummy; } ;
struct json_token {scalar_t__ type; scalar_t__ string; } ;

/* Variables and functions */
 scalar_t__ JSON_STRING ; 
 unsigned char* base64_url_decode (unsigned char const*,int /*<<< orphan*/ ,size_t*) ; 
 struct json_token* json_get_member (struct json_token*,char const*) ; 
 int /*<<< orphan*/  os_free (unsigned char*) ; 
 int /*<<< orphan*/  os_strlen (scalar_t__) ; 
 struct wpabuf* wpabuf_alloc_ext_data (unsigned char*,size_t) ; 

struct wpabuf * json_get_member_base64url(struct json_token *json,
					  const char *name)
{
	struct json_token *token;
	unsigned char *buf;
	size_t buflen;
	struct wpabuf *ret;

	token = json_get_member(json, name);
	if (!token || token->type != JSON_STRING)
		return NULL;
	buf = base64_url_decode((const unsigned char *) token->string,
				os_strlen(token->string), &buflen);
	if (!buf)
		return NULL;
	ret = wpabuf_alloc_ext_data(buf, buflen);
	if (!ret)
		os_free(buf);

	return ret;
}