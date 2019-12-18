#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ntlm_buf {int dummy; } ;
typedef  TYPE_1__* ntlm_name ;
struct TYPE_3__ {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ from_file (char const*,int /*<<< orphan*/ ,char**,struct ntlm_buf*) ; 
 char* getenv (char*) ; 
 scalar_t__ issuid () ; 

__attribute__((used)) static int
get_user_file(const ntlm_name target_name,
	      char **username, struct ntlm_buf *key)
{
    const char *fn;

    if (issuid())
	return ENOENT;

    fn = getenv("NTLM_USER_FILE");
    if (fn == NULL)
	return ENOENT;
    if (from_file(fn, target_name->domain, username, key) == 0)
	return 0;

    return ENOENT;
}