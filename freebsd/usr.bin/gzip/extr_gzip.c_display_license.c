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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* gzip_copyright ; 
 char* gzip_version ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
display_license(void)
{

	fprintf(stderr, "%s (based on NetBSD gzip 20150113)\n", gzip_version);
	fprintf(stderr, "%s\n", gzip_copyright);
	exit(0);
}