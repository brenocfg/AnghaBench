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
struct TYPE_2__ {char* username; int /*<<< orphan*/  password; } ;
typedef  TYPE_1__ git_cred_userpass_payload ;
typedef  int /*<<< orphan*/  git_cred ;

/* Variables and functions */
 unsigned int GIT_CREDTYPE_USERNAME ; 
 unsigned int GIT_CREDTYPE_USERPASS_PLAINTEXT ; 
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 int git_cred_username_new (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ git_cred_userpass_plaintext_new (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 

int git_cred_userpass(
		git_cred **cred,
		const char *url,
		const char *user_from_url,
		unsigned int allowed_types,
		void *payload)
{
	git_cred_userpass_payload *userpass = (git_cred_userpass_payload*)payload;
	const char *effective_username = NULL;

	GIT_UNUSED(url);

	if (!userpass || !userpass->password) return -1;

	/* Username resolution: a username can be passed with the URL, the
	 * credentials payload, or both. Here's what we do.  Note that if we get
	 * this far, we know that any password the url may contain has already
	 * failed at least once, so we ignore it.
	 *
	 * |  Payload    |   URL    |   Used    |
	 * +-------------+----------+-----------+
	 * |    yes      |   no     |  payload  |
	 * |    yes      |   yes    |  payload  |
	 * |    no       |   yes    |  url      |
	 * |    no       |   no     |  FAIL     |
	 */
	if (userpass->username)
		effective_username = userpass->username;
	else if (user_from_url)
		effective_username = user_from_url;
	else
		return -1;

	if (GIT_CREDTYPE_USERNAME & allowed_types)
		return git_cred_username_new(cred, effective_username);

	if ((GIT_CREDTYPE_USERPASS_PLAINTEXT & allowed_types) == 0 ||
			git_cred_userpass_plaintext_new(cred, effective_username, userpass->password) < 0)
		return -1;

	return 0;
}