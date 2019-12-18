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
typedef  size_t u_int32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  VIS_CSTYLE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  vis (char*,char const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_xml_string(FILE *fp, const char *str, size_t len)
{
	u_int32_t i;
	char visbuf[5];

	if (len == 0)
		return;

	for (i = 0; i < len; i++) {
		switch (str[i]) {
		case '\0':
			return;

		case '&':
			(void) fprintf(fp, "&amp;");
			break;

		case '<':
			(void) fprintf(fp, "&lt;");
			break;

		case '>':
			(void) fprintf(fp, "&gt;");
			break;

		case '\"':
			(void) fprintf(fp, "&quot;");
			break;

		case '\'':
			(void) fprintf(fp, "&apos;");
			break;

		default:
			(void) vis(visbuf, str[i], VIS_CSTYLE, 0);
			(void) fprintf(fp, "%s", visbuf);
			break;
		}
	}
}