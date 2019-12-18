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
 int /*<<< orphan*/  LINE (char*,char*) ; 

const char *
mdoc_a2att(const char *p)
{

	LINE("v1",	"Version\\~1 AT&T UNIX");
	LINE("v2",	"Version\\~2 AT&T UNIX");
	LINE("v3",	"Version\\~3 AT&T UNIX");
	LINE("v4",	"Version\\~4 AT&T UNIX");
	LINE("v5",	"Version\\~5 AT&T UNIX");
	LINE("v6",	"Version\\~6 AT&T UNIX");
	LINE("v7",	"Version\\~7 AT&T UNIX");
	LINE("32v",	"Version\\~32V AT&T UNIX");
	LINE("III",	"AT&T System\\~III UNIX");
	LINE("V",	"AT&T System\\~V UNIX");
	LINE("V.1",	"AT&T System\\~V Release\\~1 UNIX");
	LINE("V.2",	"AT&T System\\~V Release\\~2 UNIX");
	LINE("V.3",	"AT&T System\\~V Release\\~3 UNIX");
	LINE("V.4",	"AT&T System\\~V Release\\~4 UNIX");

	return NULL;
}