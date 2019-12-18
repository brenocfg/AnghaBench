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
typedef  int u_char ;
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 int DUMP_BYTES_PER_LINE ; 
 scalar_t__ isprint (int const) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int strlen (char*) ; 

void
DumpAscii(const u_char *buf, int len)
{
	char ch, sbuf[100];
	int k, count;

	for (count = 0; count < len; count += DUMP_BYTES_PER_LINE) {
		snprintf(sbuf, sizeof(sbuf), "%04x:  ", count);
		for (k = 0; k < DUMP_BYTES_PER_LINE; k++) {
			if (count + k < len) {
				snprintf(sbuf + strlen(sbuf),
				    sizeof(sbuf) - strlen(sbuf),
				    "%02x ", buf[count + k]);
			} else {
				snprintf(sbuf + strlen(sbuf),
				    sizeof(sbuf) - strlen(sbuf), "   ");
			}
		}
		snprintf(sbuf + strlen(sbuf), sizeof(sbuf) - strlen(sbuf), " ");
		for (k = 0; k < DUMP_BYTES_PER_LINE; k++) {
			if (count + k < len) {
				ch = isprint(buf[count + k]) ?
				    buf[count + k] : '.';
				snprintf(sbuf + strlen(sbuf),
				    sizeof(sbuf) - strlen(sbuf), "%c", ch);
			} else {
				snprintf(sbuf + strlen(sbuf),
				    sizeof(sbuf) - strlen(sbuf), " ");
			}
		}
		printf("%s\n", sbuf);
	}
}