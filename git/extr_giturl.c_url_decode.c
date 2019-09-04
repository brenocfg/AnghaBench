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
 int /*<<< orphan*/  strlen (char const*) ; 
 char* url_decode_mem (char const*,int /*<<< orphan*/ ) ; 

char *url_decode(const char *url)
{
	return url_decode_mem(url, strlen(url));
}