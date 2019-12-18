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
struct padctl_softc {int dummy; } ;
struct padctl_pad {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int nitems (struct padctl_pad*) ; 
 struct padctl_pad* pads_tbl ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct padctl_pad *
search_pad(struct padctl_softc *sc, char *pad_name)
{
	int i;

	for (i = 0; i < nitems(pads_tbl); i++) {
		if (strcmp(pad_name, pads_tbl[i].name) == 0)
			return 	(pads_tbl + i);
	}
	return (NULL);
}