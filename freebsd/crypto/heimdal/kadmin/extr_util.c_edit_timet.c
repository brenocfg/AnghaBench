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
typedef  int /*<<< orphan*/  krb5_timestamp ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ get_response (char const*,char*,char*,int) ; 
 scalar_t__ parse_timet (char*,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  time_t2str (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

int
edit_timet (const char *prompt, krb5_timestamp *value, int *mask, int bit)
{
    char buf[1024], resp[1024];

    if (mask && (*mask & bit))
	return 0;

    time_t2str (*value, buf, sizeof (buf), 0);

    for (;;) {
	if(get_response(prompt, buf, resp, sizeof(resp)) != 0)
	    return 1;
	if (parse_timet (resp, value, mask, bit) == 0)
	    break;
    }
    return 0;
}