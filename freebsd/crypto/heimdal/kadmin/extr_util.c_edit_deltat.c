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
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  krb5_deltat ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  deltat2str (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ get_response (char const*,char*,char*,int) ; 
 scalar_t__ parse_deltat (char*,int /*<<< orphan*/ *,int*,int) ; 

int
edit_deltat (const char *prompt, krb5_deltat *value, int *mask, int bit)
{
    char buf[1024], resp[1024];

    if (mask && (*mask & bit))
	return 0;

    deltat2str(*value, buf, sizeof(buf));
    for (;;) {
	if(get_response(prompt, buf, resp, sizeof(resp)) != 0)
	    return 1;
	if (parse_deltat (resp, value, mask, bit) == 0)
	    break;
    }
    return 0;
}