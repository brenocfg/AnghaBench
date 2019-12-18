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
struct strbuf {char* buf; } ;

/* Variables and functions */
 scalar_t__ starts_with (char*,char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int count_messages(struct strbuf *all_msgs)
{
	int count = 0;
	char *p = all_msgs->buf;

	while (1) {
		if (starts_with(p, "From ")) {
			p = strstr(p+5, "\nFrom: ");
			if (!p) break;
			p = strstr(p+7, "\nDate: ");
			if (!p) break;
			p = strstr(p+7, "\nSubject: ");
			if (!p) break;
			p += 10;
			count++;
		}
		p = strstr(p+5, "\nFrom ");
		if (!p)
			break;
		p++;
	}
	return count;
}