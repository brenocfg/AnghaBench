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
typedef  int /*<<< orphan*/  yaml_token_t ;
typedef  int /*<<< orphan*/  yaml_parser_t ;
typedef  int /*<<< orphan*/  yaml_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yaml_get_version (int*,int*,int*) ; 
 int /*<<< orphan*/  yaml_get_version_string () ; 

int
main(void)
{
    int major = -1;
    int minor = -1;
    int patch = -1;
    char buf[64];

    yaml_get_version(&major, &minor, &patch);
    sprintf(buf, "%d.%d.%d", major, minor, patch);
    assert(strcmp(buf, yaml_get_version_string()) == 0);

    /* Print structure sizes. */
    printf("sizeof(token) = %d\n", sizeof(yaml_token_t));
    printf("sizeof(event) = %d\n", sizeof(yaml_event_t));
    printf("sizeof(parser) = %d\n", sizeof(yaml_parser_t));

    return 0;
}