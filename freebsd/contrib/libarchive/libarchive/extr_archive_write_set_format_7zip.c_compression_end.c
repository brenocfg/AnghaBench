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
struct la_zstream {int (* end ) (struct archive*,struct la_zstream*) ;int /*<<< orphan*/ * props; scalar_t__ prop_size; scalar_t__ valid; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int stub1 (struct archive*,struct la_zstream*) ; 

__attribute__((used)) static int
compression_end(struct archive *a, struct la_zstream *lastrm)
{
	if (lastrm->valid) {
		lastrm->prop_size = 0;
		free(lastrm->props);
		lastrm->props = NULL;
		return (lastrm->end(a, lastrm));
	}
	return (ARCHIVE_OK);
}