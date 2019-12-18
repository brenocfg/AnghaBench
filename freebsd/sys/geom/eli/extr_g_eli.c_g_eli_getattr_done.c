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
struct bio {scalar_t__ bio_error; int /*<<< orphan*/  bio_length; int /*<<< orphan*/  bio_data; int /*<<< orphan*/  bio_attribute; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_std_done (struct bio*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_eli_getattr_done(struct bio *bp)
{
	if (bp->bio_error == 0 && 
	    !strcmp(bp->bio_attribute, "GEOM::physpath")) {
		strlcat(bp->bio_data, "/eli", bp->bio_length);
	}
	g_std_done(bp);
}