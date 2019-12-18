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
typedef  int /*<<< orphan*/  alist_t ;

/* Variables and functions */
 int /*<<< orphan*/ * load_file (char*) ; 
 int /*<<< orphan*/ * load_http (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

alist_t *
load_url(char *url)
{
	alist_t *hosts = NULL;

	if (strncmp(url, "file://", 7) == 0) {
		/*
		 * file:///etc/passwd
		 *        ^------------s
		 */
		hosts = load_file(url);

	} else if (*url == '/' || *url == '.') {
		hosts = load_file(url);

	} else if (strncmp(url, "http://", 7) == 0) {
		hosts = load_http(url);
	}

	return hosts;
}