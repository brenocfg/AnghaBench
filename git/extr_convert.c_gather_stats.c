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
struct text_stat {int /*<<< orphan*/  nonprintable; int /*<<< orphan*/  printable; int /*<<< orphan*/  nul; int /*<<< orphan*/  lonelf; int /*<<< orphan*/  lonecr; int /*<<< orphan*/  crlf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct text_stat*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gather_stats(const char *buf, unsigned long size, struct text_stat *stats)
{
	unsigned long i;

	memset(stats, 0, sizeof(*stats));

	for (i = 0; i < size; i++) {
		unsigned char c = buf[i];
		if (c == '\r') {
			if (i+1 < size && buf[i+1] == '\n') {
				stats->crlf++;
				i++;
			} else
				stats->lonecr++;
			continue;
		}
		if (c == '\n') {
			stats->lonelf++;
			continue;
		}
		if (c == 127)
			/* DEL */
			stats->nonprintable++;
		else if (c < 32) {
			switch (c) {
				/* BS, HT, ESC and FF */
			case '\b': case '\t': case '\033': case '\014':
				stats->printable++;
				break;
			case 0:
				stats->nul++;
				/* fall through */
			default:
				stats->nonprintable++;
			}
		}
		else
			stats->printable++;
	}

	/* If file ends with EOF then don't count this EOF as non-printable. */
	if (size >= 1 && buf[size-1] == '\032')
		stats->nonprintable--;
}