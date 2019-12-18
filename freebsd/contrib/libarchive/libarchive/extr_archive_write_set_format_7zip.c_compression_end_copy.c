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
struct la_zstream {scalar_t__ valid; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 

__attribute__((used)) static int
compression_end_copy(struct archive *a, struct la_zstream *lastrm)
{
	(void)a; /* UNUSED */
	lastrm->valid = 0;
	return (ARCHIVE_OK);
}