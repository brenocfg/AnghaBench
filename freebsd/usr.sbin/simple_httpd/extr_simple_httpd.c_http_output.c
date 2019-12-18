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
 int /*<<< orphan*/  con_sock ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
http_output(const char *html)
{
	write(con_sock, html, strlen(html));
	write(con_sock, "\r\n", 2);
}