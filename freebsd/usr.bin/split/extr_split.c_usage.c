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
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	(void)fprintf(stderr,
"usage: split [-l line_count] [-a suffix_length] [file [prefix]]\n"
"       split -b byte_count[K|k|M|m|G|g] [-a suffix_length] [file [prefix]]\n"
"       split -n chunk_count [-a suffix_length] [file [prefix]]\n"
"       split -p pattern [-a suffix_length] [file [prefix]]\n");
	exit(EX_USAGE);
}