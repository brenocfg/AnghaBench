#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uintmax_t ;
struct sun_disklabel {int sl_ncylinders; int sl_ntracks; int sl_nsectors; TYPE_1__* sl_part; } ;
struct TYPE_2__ {int sdkp_nsectors; } ;

/* Variables and functions */
 scalar_t__ cflag ; 
 int roundup (int,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strtoumax (char*,char**,int) ; 

__attribute__((used)) static int
parse_size(struct sun_disklabel *sl, int part, char *size)
{
	uintmax_t nsectors;
	uintmax_t total;
	uintmax_t n;
	char *p;
	int i;

	nsectors = 0;
	n = strtoumax(size, &p, 10);
	if (*p != '\0') {
		if (strcmp(size, "*") == 0) {
			total = sl->sl_ncylinders * sl->sl_ntracks *
			    sl->sl_nsectors;
			for (i = 0; i < part; i++) {
				if (i == 2)
					continue;
				nsectors += sl->sl_part[i].sdkp_nsectors;
			}
			n = total - nsectors;
		} else if (p[1] == '\0' && (p[0] == 'C' || p[0] == 'c')) {
			n = n * sl->sl_ntracks * sl->sl_nsectors;
		} else if (p[1] == '\0' && (p[0] == 'K' || p[0] == 'k')) {
			n = roundup((n * 1024) / 512,
			    sl->sl_ntracks * sl->sl_nsectors);
		} else if (p[1] == '\0' && (p[0] == 'M' || p[0] == 'm')) {
			n = roundup((n * 1024 * 1024) / 512,
			    sl->sl_ntracks * sl->sl_nsectors);
		} else if (p[1] == '\0' && (p[0] == 'S' || p[0] == 's')) {
			/* size in sectors, no action neded */
		} else if (p[1] == '\0' && (p[0] == 'G' || p[0] == 'g')) {
			n = roundup((n * 1024 * 1024 * 1024) / 512,
			    sl->sl_ntracks * sl->sl_nsectors);
		} else
			return (-1);
	} else if (cflag) {
		n = n * sl->sl_ntracks * sl->sl_nsectors;
	}
	sl->sl_part[part].sdkp_nsectors = n;
	return (0);
}